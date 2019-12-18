#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct g_consumer {TYPE_1__* provider; } ;
struct fs {int fs_flags; struct fs* fs_csp; int /*<<< orphan*/  fs_sblockloc; scalar_t__ fs_clean; } ;
struct TYPE_2__ {int sectorsize; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int FS_NEEDSFSCK ; 
 int FS_UNCLEAN ; 
 int /*<<< orphan*/  GJ_DEBUG (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  M_GEOM ; 
 int SBLOCKSIZE ; 
 int /*<<< orphan*/  STDSB ; 
 scalar_t__ ffs_sbget (struct g_consumer*,struct fs**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ffs_sbput (struct g_consumer*,struct fs*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_free (struct fs*) ; 
 int /*<<< orphan*/  g_use_g_read_data ; 
 int /*<<< orphan*/  g_use_g_write_data ; 

__attribute__((used)) static void
g_journal_ufs_dirty(struct g_consumer *cp)
{
	struct fs *fs;
	int error;

	fs = NULL;
	if (SBLOCKSIZE % cp->provider->sectorsize != 0 ||
	    ffs_sbget(cp, &fs, STDSB, M_GEOM, g_use_g_read_data) != 0) {
		GJ_DEBUG(0, "Cannot find superblock to mark file system %s "
		    "as dirty.", cp->provider->name);
		KASSERT(fs == NULL,
		    ("g_journal_ufs_dirty: non-NULL fs %p\n", fs));
		return;
	}
	GJ_DEBUG(0, "clean=%d flags=0x%x", fs->fs_clean, fs->fs_flags);
	fs->fs_clean = 0;
	fs->fs_flags |= FS_NEEDSFSCK | FS_UNCLEAN;
	error = ffs_sbput(cp, fs, fs->fs_sblockloc, g_use_g_write_data);
	g_free(fs->fs_csp);
	g_free(fs);
	if (error != 0) {
		GJ_DEBUG(0, "Cannot mark file system %s as dirty "
		    "(error=%d).", cp->provider->name, error);
	} else {
		GJ_DEBUG(0, "File system %s marked as dirty.",
		    cp->provider->name);
	}
}