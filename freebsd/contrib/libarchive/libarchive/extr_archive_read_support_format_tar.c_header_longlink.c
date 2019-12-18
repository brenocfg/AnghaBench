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
struct TYPE_2__ {int /*<<< orphan*/  s; } ;
struct tar {TYPE_1__ longlink; } ;
struct archive_read {int dummy; } ;
struct archive_entry {int dummy; } ;

/* Variables and functions */
 int ARCHIVE_OK ; 
 int ARCHIVE_WARN ; 
 int /*<<< orphan*/  archive_entry_copy_link (struct archive_entry*,int /*<<< orphan*/ ) ; 
 int read_body_to_string (struct archive_read*,struct tar*,TYPE_1__*,void const*,size_t*) ; 
 int tar_read_header (struct archive_read*,struct tar*,struct archive_entry*,size_t*) ; 

__attribute__((used)) static int
header_longlink(struct archive_read *a, struct tar *tar,
    struct archive_entry *entry, const void *h, size_t *unconsumed)
{
	int err;

	err = read_body_to_string(a, tar, &(tar->longlink), h, unconsumed);
	if (err != ARCHIVE_OK)
		return (err);
	err = tar_read_header(a, tar, entry, unconsumed);
	if ((err != ARCHIVE_OK) && (err != ARCHIVE_WARN))
		return (err);
	/* Set symlink if symlink already set, else hardlink. */
	archive_entry_copy_link(entry, tar->longlink.s);
	return (ARCHIVE_OK);
}