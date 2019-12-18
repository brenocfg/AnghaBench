#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct TYPE_7__ {char* spa_name; } ;
typedef  TYPE_1__ spa_t ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,...) ; 
 TYPE_1__* spa ; 
 TYPE_1__* spa_find_by_name (char*) ; 
 char* strchr (char*,char) ; 
 scalar_t__ zfs_lookup_dataset (TYPE_1__*,char*,scalar_t__*) ; 
 scalar_t__ zfs_mount (TYPE_1__*,scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ zfs_spa_init (TYPE_1__*) ; 
 int /*<<< orphan*/  zfsmount ; 

__attribute__((used)) static int
zfs_mount_ds(char *dsname)
{
    uint64_t newroot;
    spa_t *newspa;
    char *q;

    q = strchr(dsname, '/');
    if (q)
	*q++ = '\0';
    newspa = spa_find_by_name(dsname);
    if (newspa == NULL) {
	printf("\nCan't find ZFS pool %s\n", dsname);
	return -1;
    }

    if (zfs_spa_init(newspa))
	return -1;

    newroot = 0;
    if (q) {
	if (zfs_lookup_dataset(newspa, q, &newroot)) {
	    printf("\nCan't find dataset %s in ZFS pool %s\n",
		    q, newspa->spa_name);
	    return -1;
	}
    }
    if (zfs_mount(newspa, newroot, &zfsmount)) {
	printf("\nCan't mount ZFS dataset\n");
	return -1;
    }
    spa = newspa;
    return (0);
}