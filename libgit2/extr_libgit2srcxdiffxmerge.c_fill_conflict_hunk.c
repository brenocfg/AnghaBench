#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int i1; int chg1; int i2; int chg2; int /*<<< orphan*/  chg0; int /*<<< orphan*/  i0; } ;
typedef  TYPE_1__ xdmerge_t ;
typedef  int /*<<< orphan*/  xdfenv_t ;

/* Variables and functions */
 int DEFAULT_CONFLICT_MARKER_SIZE ; 
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC_ADD (size_t*,size_t,size_t) ; 
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC_ADD4 (size_t*,size_t,int,int,int) ; 
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC_ADD5 (size_t*,size_t,int,int,int,int) ; 
 int XDL_MERGE_DIFF3 ; 
 int is_cr_needed (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int /*<<< orphan*/  memset (char*,char,int) ; 
 scalar_t__ strlen (char const*) ; 
 scalar_t__ xdl_orig_copy (size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,char*) ; 
 scalar_t__ xdl_recs_copy (size_t*,int /*<<< orphan*/ *,int,int,int,int,char*) ; 

__attribute__((used)) static int fill_conflict_hunk(size_t *out, xdfenv_t *xe1, const char *name1,
			      xdfenv_t *xe2, const char *name2,
			      const char *name3,
			      size_t size, int i, int style,
			      xdmerge_t *m, char *dest, int marker_size)
{
	int marker1_size = (name1 ? (int)strlen(name1) + 1 : 0);
	int marker2_size = (name2 ? (int)strlen(name2) + 1 : 0);
	int marker3_size = (name3 ? (int)strlen(name3) + 1 : 0);
	int needs_cr = is_cr_needed(xe1, xe2, m);
	size_t copied;

	*out = 0;

	if (marker_size <= 0)
		marker_size = DEFAULT_CONFLICT_MARKER_SIZE;

	/* Before conflicting part */
	if (xdl_recs_copy(&copied, xe1, i, m->i1 - i, 0, 0,
			      dest ? dest + size : NULL) < 0)
		return -1;

	GIT_ERROR_CHECK_ALLOC_ADD(&size, size, copied);

	if (!dest) {
		GIT_ERROR_CHECK_ALLOC_ADD5(&size, size, marker_size, 1, needs_cr,  marker1_size);
	} else {
		memset(dest + size, '<', marker_size);
		size += marker_size;
		if (marker1_size) {
			dest[size] = ' ';
			memcpy(dest + size + 1, name1, marker1_size - 1);
			size += marker1_size;
		}
		if (needs_cr)
			dest[size++] = '\r';
		dest[size++] = '\n';
	}

	/* Postimage from side #1 */
	if (xdl_recs_copy(&copied, xe1, m->i1, m->chg1, needs_cr, 1,
			      dest ? dest + size : NULL) < 0)
		return -1;

	GIT_ERROR_CHECK_ALLOC_ADD(&size, size, copied);

	if (style == XDL_MERGE_DIFF3) {
		/* Shared preimage */
		if (!dest) {
			GIT_ERROR_CHECK_ALLOC_ADD5(&size, size, marker_size, 1, needs_cr, marker3_size);
		} else {
			memset(dest + size, '|', marker_size);
			size += marker_size;
			if (marker3_size) {
				dest[size] = ' ';
				memcpy(dest + size + 1, name3, marker3_size - 1);
				size += marker3_size;
			}
			if (needs_cr)
				dest[size++] = '\r';
			dest[size++] = '\n';
		}

		if (xdl_orig_copy(&copied, xe1, m->i0, m->chg0, needs_cr, 1,
				      dest ? dest + size : NULL) < 0)
			return -1;
		GIT_ERROR_CHECK_ALLOC_ADD(&size, size, copied);
	}

	if (!dest) {
		GIT_ERROR_CHECK_ALLOC_ADD4(&size, size, marker_size, 1, needs_cr);
	} else {
		memset(dest + size, '=', marker_size);
		size += marker_size;
		if (needs_cr)
			dest[size++] = '\r';
		dest[size++] = '\n';
	}

	/* Postimage from side #2 */

	if (xdl_recs_copy(&copied, xe2, m->i2, m->chg2, needs_cr, 1,
			      dest ? dest + size : NULL) < 0)
		return -1;
	GIT_ERROR_CHECK_ALLOC_ADD(&size, size, copied);

	if (!dest) {
		GIT_ERROR_CHECK_ALLOC_ADD5(&size, size, marker_size, 1, needs_cr, marker2_size);
	} else {
		memset(dest + size, '>', marker_size);
		size += marker_size;
		if (marker2_size) {
			dest[size] = ' ';
			memcpy(dest + size + 1, name2, marker2_size - 1);
			size += marker2_size;
		}
		if (needs_cr)
			dest[size++] = '\r';
		dest[size++] = '\n';
	}

	*out = size;
	return 0;
}