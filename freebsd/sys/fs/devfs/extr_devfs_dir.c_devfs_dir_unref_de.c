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
struct devfs_mount {int dummy; } ;
struct devfs_dirent {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SPECNAMELEN ; 
 int /*<<< orphan*/  devfs_dir_unref (char*) ; 
 char* devfs_fqpn (char*,struct devfs_mount*,struct devfs_dirent*,int /*<<< orphan*/ *) ; 

void
devfs_dir_unref_de(struct devfs_mount *dm, struct devfs_dirent *de)
{
	char dirname[SPECNAMELEN + 1], *namep;

	namep = devfs_fqpn(dirname, dm, de, NULL);
	KASSERT(namep != NULL, ("devfs_unref_dir_de: NULL namep"));

	devfs_dir_unref(namep);
}