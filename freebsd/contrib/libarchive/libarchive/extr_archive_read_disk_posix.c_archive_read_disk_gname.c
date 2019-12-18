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
struct archive_read_disk {char const* (* lookup_gname ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  lookup_gname_data; } ;
struct archive {int dummy; } ;
typedef  int /*<<< orphan*/  la_int64_t ;

/* Variables and functions */
 scalar_t__ ARCHIVE_OK ; 
 int /*<<< orphan*/  ARCHIVE_READ_DISK_MAGIC ; 
 int /*<<< orphan*/  ARCHIVE_STATE_ANY ; 
 scalar_t__ __archive_check_magic (struct archive*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 char const* stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

const char *
archive_read_disk_gname(struct archive *_a, la_int64_t gid)
{
	struct archive_read_disk *a = (struct archive_read_disk *)_a;
	if (ARCHIVE_OK != __archive_check_magic(_a, ARCHIVE_READ_DISK_MAGIC,
		ARCHIVE_STATE_ANY, "archive_read_disk_gname"))
		return (NULL);
	if (a->lookup_gname == NULL)
		return (NULL);
	return ((*a->lookup_gname)(a->lookup_gname_data, gid));
}