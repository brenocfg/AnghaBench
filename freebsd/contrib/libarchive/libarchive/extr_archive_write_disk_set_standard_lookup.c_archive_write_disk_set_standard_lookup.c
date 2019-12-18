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
struct bucket {int dummy; } ;
struct archive {int dummy; } ;

/* Variables and functions */
 int ARCHIVE_FATAL ; 
 int ARCHIVE_OK ; 
 int /*<<< orphan*/  archive_write_disk_set_group_lookup (struct archive*,struct bucket*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_write_disk_set_user_lookup (struct archive*,struct bucket*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cache_size ; 
 struct bucket* calloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cleanup ; 
 int /*<<< orphan*/  free (struct bucket*) ; 
 int /*<<< orphan*/  lookup_gid ; 
 int /*<<< orphan*/  lookup_uid ; 

int
archive_write_disk_set_standard_lookup(struct archive *a)
{
	struct bucket *ucache = calloc(cache_size, sizeof(struct bucket));
	struct bucket *gcache = calloc(cache_size, sizeof(struct bucket));
	if (ucache == NULL || gcache == NULL) {
		free(ucache);
		free(gcache);
		return (ARCHIVE_FATAL);
	}
	archive_write_disk_set_group_lookup(a, gcache, lookup_gid, cleanup);
	archive_write_disk_set_user_lookup(a, ucache, lookup_uid, cleanup);
	return (ARCHIVE_OK);
}