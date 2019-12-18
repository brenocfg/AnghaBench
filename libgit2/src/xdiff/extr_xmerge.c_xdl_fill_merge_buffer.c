#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int mode; int i1; int chg1; int i2; int chg2; struct TYPE_15__* next; } ;
typedef  TYPE_2__ xdmerge_t ;
struct TYPE_14__ {int nrec; } ;
struct TYPE_16__ {TYPE_1__ xdf2; } ;
typedef  TYPE_3__ xdfenv_t ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC_ADD (size_t*,size_t,size_t) ; 
 scalar_t__ fill_conflict_hunk (size_t*,TYPE_3__*,char const*,TYPE_3__*,char const*,char const*,size_t,int,int,TYPE_2__*,char*,int) ; 
 int is_cr_needed (TYPE_3__*,TYPE_3__*,TYPE_2__*) ; 
 scalar_t__ xdl_recs_copy (size_t*,TYPE_3__*,int,int,int,int,char*) ; 

__attribute__((used)) static int xdl_fill_merge_buffer(size_t *out,
				 xdfenv_t *xe1, const char *name1,
				 xdfenv_t *xe2, const char *name2,
				 const char *ancestor_name,
				 int favor,
				 xdmerge_t *m, char *dest, int style,
				 int marker_size)
{
	size_t size, copied;
	int i;

	*out = 0;

	for (size = i = 0; m; m = m->next) {
		if (favor && !m->mode)
			m->mode = favor;

		if (m->mode == 0) {
			if (fill_conflict_hunk(&size, xe1, name1, xe2, name2,
						  ancestor_name,
						  size, i, style, m, dest,
						  marker_size) < 0)
				return -1;
		}
		else if (m->mode & 3) {
			/* Before conflicting part */
			if (xdl_recs_copy(&copied, xe1, i, m->i1 - i, 0, 0,
					      dest ? dest + size : NULL) < 0)
				return -1;
			GIT_ERROR_CHECK_ALLOC_ADD(&size, size, copied);

			/* Postimage from side #1 */
			if (m->mode & 1) {
				int needs_cr = is_cr_needed(xe1, xe2, m);

				if (xdl_recs_copy(&copied, xe1, m->i1, m->chg1, needs_cr, (m->mode & 2),
						      dest ? dest + size : NULL) < 0)
					return -1;
				GIT_ERROR_CHECK_ALLOC_ADD(&size, size, copied);
			}

			/* Postimage from side #2 */
			if (m->mode & 2) {
				if (xdl_recs_copy(&copied, xe2, m->i2, m->chg2, 0, 0,
						      dest ? dest + size : NULL) < 0)
					return -1;
				GIT_ERROR_CHECK_ALLOC_ADD(&size, size, copied);
			}
		} else
			continue;
		i = m->i1 + m->chg1;
	}

	if (xdl_recs_copy(&copied, xe1, i, xe1->xdf2.nrec - i, 0, 0,
			      dest ? dest + size : NULL) < 0)
		return -1;
	GIT_ERROR_CHECK_ALLOC_ADD(&size, size, copied);

	*out = size;
	return 0;
}