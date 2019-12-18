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
struct archive_write {int /*<<< orphan*/ * format_data; } ;
struct ar_w {scalar_t__ has_strtab; struct ar_w* strtab; } ;

/* Variables and functions */
 int ARCHIVE_OK ; 
 int /*<<< orphan*/  free (struct ar_w*) ; 

__attribute__((used)) static int
archive_write_ar_free(struct archive_write *a)
{
	struct ar_w *ar;

	ar = (struct ar_w *)a->format_data;

	if (ar == NULL)
		return (ARCHIVE_OK);

	if (ar->has_strtab > 0) {
		free(ar->strtab);
		ar->strtab = NULL;
	}

	free(ar);
	a->format_data = NULL;
	return (ARCHIVE_OK);
}