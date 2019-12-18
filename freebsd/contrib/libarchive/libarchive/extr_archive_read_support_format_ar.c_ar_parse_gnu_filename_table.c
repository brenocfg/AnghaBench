#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct archive_read {int /*<<< orphan*/  archive; TYPE_1__* format; } ;
struct ar {size_t strtab_size; char* strtab; } ;
struct TYPE_2__ {scalar_t__ data; } ;

/* Variables and functions */
 int ARCHIVE_FATAL ; 
 int ARCHIVE_OK ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  archive_set_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (char*) ; 

__attribute__((used)) static int
ar_parse_gnu_filename_table(struct archive_read *a)
{
	struct ar *ar;
	char *p;
	size_t size;

	ar = (struct ar*)(a->format->data);
	size = ar->strtab_size;

	for (p = ar->strtab; p < ar->strtab + size - 1; ++p) {
		if (*p == '/') {
			*p++ = '\0';
			if (*p != '\n')
				goto bad_string_table;
			*p = '\0';
		}
	}
	/*
	 * GNU ar always pads the table to an even size.
	 * The pad character is either '\n' or '`'.
	 */
	if (p != ar->strtab + size && *p != '\n' && *p != '`')
		goto bad_string_table;

	/* Enforce zero termination. */
	ar->strtab[size - 1] = '\0';

	return (ARCHIVE_OK);

bad_string_table:
	archive_set_error(&a->archive, EINVAL,
	    "Invalid string table");
	free(ar->strtab);
	ar->strtab = NULL;
	return (ARCHIVE_FATAL);
}