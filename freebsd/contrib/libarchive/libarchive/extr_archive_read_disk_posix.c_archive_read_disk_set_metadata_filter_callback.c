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
struct archive_read_disk {int (* metadata_filter_func ) (struct archive*,void*,struct archive_entry*) ;void* metadata_filter_data; } ;
struct archive {int dummy; } ;

/* Variables and functions */
 int ARCHIVE_OK ; 
 int /*<<< orphan*/  ARCHIVE_READ_DISK_MAGIC ; 
 int /*<<< orphan*/  ARCHIVE_STATE_ANY ; 
 int /*<<< orphan*/  archive_check_magic (struct archive*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

int
archive_read_disk_set_metadata_filter_callback(struct archive *_a,
    int (*_metadata_filter_func)(struct archive *, void *,
    struct archive_entry *), void *_client_data)
{
	struct archive_read_disk *a = (struct archive_read_disk *)_a;

	archive_check_magic(_a, ARCHIVE_READ_DISK_MAGIC, ARCHIVE_STATE_ANY,
	    "archive_read_disk_set_metadata_filter_callback");

	a->metadata_filter_func = _metadata_filter_func;
	a->metadata_filter_data = _client_data;
	return (ARCHIVE_OK);
}