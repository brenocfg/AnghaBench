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
 int XDL_MERGE_DIFF3 ; 
 int is_cr_needed (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int /*<<< orphan*/  memset (char*,char,int) ; 
 int strlen (char const*) ; 
 scalar_t__ xdl_orig_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,char*) ; 
 scalar_t__ xdl_recs_copy (int /*<<< orphan*/ *,int,int,int,int,char*) ; 

__attribute__((used)) static int fill_conflict_hunk(xdfenv_t *xe1, const char *name1,
			      xdfenv_t *xe2, const char *name2,
			      const char *name3,
			      int size, int i, int style,
			      xdmerge_t *m, char *dest, int marker_size)
{
	int marker1_size = (name1 ? strlen(name1) + 1 : 0);
	int marker2_size = (name2 ? strlen(name2) + 1 : 0);
	int marker3_size = (name3 ? strlen(name3) + 1 : 0);
	int needs_cr = is_cr_needed(xe1, xe2, m);

	if (marker_size <= 0)
		marker_size = DEFAULT_CONFLICT_MARKER_SIZE;

	/* Before conflicting part */
	size += xdl_recs_copy(xe1, i, m->i1 - i, 0, 0,
			      dest ? dest + size : NULL);

	if (!dest) {
		size += marker_size + 1 + needs_cr + marker1_size;
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
	size += xdl_recs_copy(xe1, m->i1, m->chg1, needs_cr, 1,
			      dest ? dest + size : NULL);

	if (style == XDL_MERGE_DIFF3) {
		/* Shared preimage */
		if (!dest) {
			size += marker_size + 1 + needs_cr + marker3_size;
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
		size += xdl_orig_copy(xe1, m->i0, m->chg0, needs_cr, 1,
				      dest ? dest + size : NULL);
	}

	if (!dest) {
		size += marker_size + 1 + needs_cr;
	} else {
		memset(dest + size, '=', marker_size);
		size += marker_size;
		if (needs_cr)
			dest[size++] = '\r';
		dest[size++] = '\n';
	}

	/* Postimage from side #2 */
	size += xdl_recs_copy(xe2, m->i2, m->chg2, needs_cr, 1,
			      dest ? dest + size : NULL);
	if (!dest) {
		size += marker_size + 1 + needs_cr + marker2_size;
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
	return size;
}