#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct repository {int dummy; } ;
struct diff_filespec {char* data; int size; int /*<<< orphan*/  oid; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC_ARRAY (unsigned long*,int) ; 
 int /*<<< orphan*/  ALLOC_GROW (unsigned long*,long,int) ; 
 int /*<<< orphan*/  REALLOC_ARRAY (unsigned long*,long) ; 
 int /*<<< orphan*/  die (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ diff_populate_filespec (struct repository*,struct diff_filespec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  oid_to_hex (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fill_line_ends(struct repository *r,
			   struct diff_filespec *spec,
			   long *lines,
			   unsigned long **line_ends)
{
	int num = 0, size = 50;
	long cur = 0;
	unsigned long *ends = NULL;
	char *data = NULL;

	if (diff_populate_filespec(r, spec, 0))
		die("Cannot read blob %s", oid_to_hex(&spec->oid));

	ALLOC_ARRAY(ends, size);
	ends[cur++] = 0;
	data = spec->data;
	while (num < spec->size) {
		if (data[num] == '\n' || num == spec->size - 1) {
			ALLOC_GROW(ends, (cur + 1), size);
			ends[cur++] = num;
		}
		num++;
	}

	/* shrink the array to fit the elements */
	REALLOC_ARRAY(ends, cur);
	*lines = cur-1;
	*line_ends = ends;
}