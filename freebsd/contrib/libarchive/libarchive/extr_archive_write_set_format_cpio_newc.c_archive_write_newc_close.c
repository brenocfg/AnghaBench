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
struct archive_write {int dummy; } ;
struct archive_entry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  archive_entry_free (struct archive_entry*) ; 
 struct archive_entry* archive_entry_new () ; 
 int /*<<< orphan*/  archive_entry_set_nlink (struct archive_entry*,int) ; 
 int /*<<< orphan*/  archive_entry_set_pathname (struct archive_entry*,char*) ; 
 int /*<<< orphan*/  archive_entry_set_size (struct archive_entry*,int /*<<< orphan*/ ) ; 
 int write_header (struct archive_write*,struct archive_entry*) ; 

__attribute__((used)) static int
archive_write_newc_close(struct archive_write *a)
{
	int er;
	struct archive_entry *trailer;

	trailer = archive_entry_new();
	archive_entry_set_nlink(trailer, 1);
	archive_entry_set_size(trailer, 0);
	archive_entry_set_pathname(trailer, "TRAILER!!!");
	/* Bypass the required data checks. */
	er = write_header(a, trailer);
	archive_entry_free(trailer);
	return (er);
}