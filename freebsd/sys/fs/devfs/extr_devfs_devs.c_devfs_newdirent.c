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
struct dirent {int d_namlen; int d_reclen; int /*<<< orphan*/  d_name; } ;
struct devfs_dirent {int de_links; int de_holdcnt; int /*<<< orphan*/  de_ctime; int /*<<< orphan*/  de_atime; int /*<<< orphan*/  de_mtime; struct dirent* de_dirent; } ;

/* Variables and functions */
 int GENERIC_DIRSIZ (struct dirent*) ; 
 int /*<<< orphan*/  M_DEVFS3 ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  bcopy (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dirent_terminate (struct dirent*) ; 
 int /*<<< orphan*/  mac_devfs_init (struct devfs_dirent*) ; 
 struct devfs_dirent* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vfs_timestamp (int /*<<< orphan*/ *) ; 

struct devfs_dirent *
devfs_newdirent(char *name, int namelen)
{
	int i;
	struct devfs_dirent *de;
	struct dirent d;

	d.d_namlen = namelen;
	i = sizeof(*de) + GENERIC_DIRSIZ(&d);
	de = malloc(i, M_DEVFS3, M_WAITOK | M_ZERO);
	de->de_dirent = (struct dirent *)(de + 1);
	de->de_dirent->d_namlen = namelen;
	de->de_dirent->d_reclen = GENERIC_DIRSIZ(&d);
	bcopy(name, de->de_dirent->d_name, namelen);
	dirent_terminate(de->de_dirent);
	vfs_timestamp(&de->de_ctime);
	de->de_mtime = de->de_atime = de->de_ctime;
	de->de_links = 1;
	de->de_holdcnt = 1;
#ifdef MAC
	mac_devfs_init(de);
#endif
	return (de);
}