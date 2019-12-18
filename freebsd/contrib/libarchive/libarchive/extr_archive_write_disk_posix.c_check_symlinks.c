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
struct archive_write_disk {int /*<<< orphan*/ * pst; int /*<<< orphan*/  archive; int /*<<< orphan*/  flags; int /*<<< orphan*/  name; } ;
struct archive_string {int /*<<< orphan*/  s; } ;

/* Variables and functions */
 int ARCHIVE_OK ; 
 int /*<<< orphan*/  archive_set_error (int /*<<< orphan*/ *,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_string_free (struct archive_string*) ; 
 int /*<<< orphan*/  archive_string_init (struct archive_string*) ; 
 int check_symlinks_fsobj (int /*<<< orphan*/ ,int*,struct archive_string*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
check_symlinks(struct archive_write_disk *a)
{
	struct archive_string error_string;
	int error_number;
	int rc;
	archive_string_init(&error_string);
	rc = check_symlinks_fsobj(a->name, &error_number, &error_string,
	    a->flags);
	if (rc != ARCHIVE_OK) {
		archive_set_error(&a->archive, error_number, "%s",
		    error_string.s);
	}
	archive_string_free(&error_string);
	a->pst = NULL;	/* to be safe */
	return rc;
}