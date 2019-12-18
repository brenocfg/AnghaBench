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
struct name_cache {void* size; struct archive* archive; } ;
struct archive {int dummy; } ;

/* Variables and functions */
 int ARCHIVE_FATAL ; 
 int ARCHIVE_OK ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  archive_read_disk_set_gname_lookup (struct archive*,struct name_cache*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_read_disk_set_uname_lookup (struct archive*,struct name_cache*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_set_error (struct archive*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  cleanup ; 
 int /*<<< orphan*/  free (struct name_cache*) ; 
 int /*<<< orphan*/  lookup_gname ; 
 int /*<<< orphan*/  lookup_uname ; 
 struct name_cache* malloc (int) ; 
 int /*<<< orphan*/  memset (struct name_cache*,int /*<<< orphan*/ ,int) ; 
 void* name_cache_size ; 

int
archive_read_disk_set_standard_lookup(struct archive *a)
{
	struct name_cache *ucache = malloc(sizeof(struct name_cache));
	struct name_cache *gcache = malloc(sizeof(struct name_cache));

	if (ucache == NULL || gcache == NULL) {
		archive_set_error(a, ENOMEM,
		    "Can't allocate uname/gname lookup cache");
		free(ucache);
		free(gcache);
		return (ARCHIVE_FATAL);
	}

	memset(ucache, 0, sizeof(*ucache));
	ucache->archive = a;
	ucache->size = name_cache_size;
	memset(gcache, 0, sizeof(*gcache));
	gcache->archive = a;
	gcache->size = name_cache_size;

	archive_read_disk_set_gname_lookup(a, gcache, lookup_gname, cleanup);
	archive_read_disk_set_uname_lookup(a, ucache, lookup_uname, cleanup);

	return (ARCHIVE_OK);
}