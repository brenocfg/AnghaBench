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
struct g_provider {int sectorsize; int /*<<< orphan*/  name; } ;
struct g_consumer {struct g_provider* provider; } ;
struct fs {scalar_t__ fs_magic; scalar_t__ fs_fsize; char* fs_volname; int* fs_id; struct fs* fs_csp; } ;

/* Variables and functions */
 scalar_t__ FS_UFS1_MAGIC ; 
 scalar_t__ FS_UFS2_MAGIC ; 
 int /*<<< orphan*/  G_LABEL_DEBUG (int,char*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ G_LABEL_UFS_CMP (struct g_provider*,struct fs*,int /*<<< orphan*/ ) ; 
#define  G_LABEL_UFS_ID 129 
#define  G_LABEL_UFS_VOLUME 128 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  M_GEOM ; 
 int SBLOCKSIZE ; 
 int /*<<< orphan*/  STDSB_NOHASHFAIL ; 
 scalar_t__ ffs_sbget (struct g_consumer*,struct fs**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fs_old_size ; 
 int /*<<< orphan*/  fs_providersize ; 
 int /*<<< orphan*/  fs_size ; 
 int /*<<< orphan*/  g_free (struct fs*) ; 
 int /*<<< orphan*/  g_topology_assert_not () ; 
 int /*<<< orphan*/  g_use_g_read_data ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,int,int) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,size_t) ; 

__attribute__((used)) static void
g_label_ufs_taste_common(struct g_consumer *cp, char *label, size_t size, int what)
{
	struct g_provider *pp;
	struct fs *fs;

	g_topology_assert_not();
	pp = cp->provider;
	label[0] = '\0';

	fs = NULL;
	if (SBLOCKSIZE % pp->sectorsize != 0 || ffs_sbget(cp, &fs,
	    STDSB_NOHASHFAIL, M_GEOM, g_use_g_read_data) != 0) {
		KASSERT(fs == NULL,
		    ("g_label_ufs_taste_common: non-NULL fs %p\n", fs));
		return;
	}

	/*
	 * Check for magic. We also need to check if file system size
	 * is almost equal to providers size, because sysinstall(8)
	 * used to bogusly put first partition at offset 0
	 * instead of 16, and glabel/ufs would find file system on slice
	 * instead of partition.
	 *
	 * In addition, media size can be a bit bigger than file system
	 * size. For instance, mkuzip can append bytes to align data
	 * to large sector size (it improves compression rates).
	 */
	if (fs->fs_magic == FS_UFS1_MAGIC && fs->fs_fsize > 0 &&
	    ( G_LABEL_UFS_CMP(pp, fs, fs_old_size)
		|| G_LABEL_UFS_CMP(pp, fs, fs_providersize))) {
		/* Valid UFS1. */
	} else if (fs->fs_magic == FS_UFS2_MAGIC && fs->fs_fsize > 0 &&
	    ( G_LABEL_UFS_CMP(pp, fs, fs_size)
		|| G_LABEL_UFS_CMP(pp, fs, fs_providersize))) {
		/* Valid UFS2. */
	} else {
		goto out;
	}
	G_LABEL_DEBUG(1, "%s file system detected on %s.",
	    fs->fs_magic == FS_UFS1_MAGIC ? "UFS1" : "UFS2", pp->name);
	switch (what) {
	case G_LABEL_UFS_VOLUME:
		/* Check for volume label */
		if (fs->fs_volname[0] != '\0')
			strlcpy(label, fs->fs_volname, size);
		break;
	case G_LABEL_UFS_ID:
		if (fs->fs_id[0] != 0 || fs->fs_id[1] != 0)
			snprintf(label, size, "%08x%08x", fs->fs_id[0],
			    fs->fs_id[1]);
		break;
	}
out:
	g_free(fs->fs_csp);
	g_free(fs);
}