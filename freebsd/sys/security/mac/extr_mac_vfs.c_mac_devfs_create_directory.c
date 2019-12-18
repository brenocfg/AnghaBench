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
struct mount {int dummy; } ;
struct devfs_dirent {int /*<<< orphan*/  de_label; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAC_POLICY_PERFORM_NOSLEEP (int /*<<< orphan*/ ,struct mount*,char*,int,struct devfs_dirent*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devfs_create_directory ; 

void
mac_devfs_create_directory(struct mount *mp, char *dirname, int dirnamelen,
    struct devfs_dirent *de)
{

	MAC_POLICY_PERFORM_NOSLEEP(devfs_create_directory, mp, dirname,
	    dirnamelen, de, de->de_label);
}