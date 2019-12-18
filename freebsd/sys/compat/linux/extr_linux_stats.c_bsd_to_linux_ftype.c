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

/* Variables and functions */
#define  LINUX_CODA_SUPER_MAGIC 140 
#define  LINUX_DEVFS_SUPER_MAGIC 139 
#define  LINUX_EXT2_SUPER_MAGIC 138 
#define  LINUX_HPFS_SUPER_MAGIC 137 
#define  LINUX_ISOFS_SUPER_MAGIC 136 
#define  LINUX_MSDOS_SUPER_MAGIC 135 
#define  LINUX_NCP_SUPER_MAGIC 134 
#define  LINUX_NFS_SUPER_MAGIC 133 
#define  LINUX_NTFS_SUPER_MAGIC 132 
#define  LINUX_PROC_SUPER_MAGIC 131 
#define  LINUX_SHMFS_MAGIC 130 
#define  LINUX_UFS_SUPER_MAGIC 129 
#define  LINUX_ZFS_SUPER_MAGIC 128 
 scalar_t__ strcmp (char const*,char const*) ; 

__attribute__((used)) static long
bsd_to_linux_ftype(const char *fstypename)
{
	int i;
	static struct {const char *bsd_name; long linux_type;} b2l_tbl[] = {
		{"ufs",     LINUX_UFS_SUPER_MAGIC},
		{"zfs",     LINUX_ZFS_SUPER_MAGIC},
		{"cd9660",  LINUX_ISOFS_SUPER_MAGIC},
		{"nfs",     LINUX_NFS_SUPER_MAGIC},
		{"ext2fs",  LINUX_EXT2_SUPER_MAGIC},
		{"procfs",  LINUX_PROC_SUPER_MAGIC},
		{"msdosfs", LINUX_MSDOS_SUPER_MAGIC},
		{"ntfs",    LINUX_NTFS_SUPER_MAGIC},
		{"nwfs",    LINUX_NCP_SUPER_MAGIC},
		{"hpfs",    LINUX_HPFS_SUPER_MAGIC},
		{"coda",    LINUX_CODA_SUPER_MAGIC},
		{"devfs",   LINUX_DEVFS_SUPER_MAGIC},
		{"tmpfs",   LINUX_SHMFS_MAGIC},
		{NULL,      0L}};

	for (i = 0; b2l_tbl[i].bsd_name != NULL; i++)
		if (strcmp(b2l_tbl[i].bsd_name, fstypename) == 0)
			return (b2l_tbl[i].linux_type);

	return (0L);
}