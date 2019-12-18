#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_8__ ;
typedef  struct TYPE_27__   TYPE_7__ ;
typedef  struct TYPE_26__   TYPE_6__ ;
typedef  struct TYPE_25__   TYPE_5__ ;
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  newname ;
struct TYPE_24__ {int rock_ridge_move_count; TYPE_8__* rr_moved_dir; int /*<<< orphan*/  rootNode; } ;
typedef  TYPE_4__ iso9660_disk ;
struct TYPE_25__ {TYPE_3__* isoDirRecord; struct TYPE_25__* rr_relocated; TYPE_8__* parent; TYPE_8__* rr_real_parent; TYPE_2__* node; } ;
typedef  TYPE_5__ cd9660node ;
struct TYPE_28__ {int /*<<< orphan*/  cn_children; TYPE_1__* isoDirRecord; } ;
struct TYPE_27__ {int /*<<< orphan*/  st_mtime; scalar_t__ st_ino; } ;
struct TYPE_26__ {int /*<<< orphan*/  tv_sec; } ;
struct TYPE_23__ {int* length; int* name_len; int /*<<< orphan*/  name; } ;
struct TYPE_22__ {int /*<<< orphan*/  name; } ;
struct TYPE_21__ {int /*<<< orphan*/  date; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISO_FILENAME_MAXLENGTH_WITH_PADDING ; 
 int /*<<< orphan*/  ISO_RRIP_DEFAULT_MOVE_DIR_NAME ; 
 scalar_t__ TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_INSERT_HEAD (int /*<<< orphan*/ *,TYPE_5__*,int /*<<< orphan*/ ) ; 
 TYPE_8__* cd9660_create_directory (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_5__*) ; 
 TYPE_5__* cd9660_create_file (TYPE_4__*,int /*<<< orphan*/ ,TYPE_8__*,TYPE_5__*) ; 
 int /*<<< orphan*/  cd9660_sorted_child_insert (TYPE_8__*,TYPE_5__*) ; 
 int /*<<< orphan*/  cd9660_time_915 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cn_next_child ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 TYPE_7__ stampst ; 
 TYPE_6__ start_time ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static cd9660node *
cd9660_rrip_move_directory(iso9660_disk *diskStructure, cd9660node *dir)
{
	char newname[9];
	cd9660node *tfile;

	/*
	 * This function needs to:
	 * 1) Create an empty virtual file in place of the old directory
	 * 2) Point the virtual file to the new directory
	 * 3) Point the relocated directory to its old parent
	 * 4) Move the directory specified by dir into rr_moved_dir,
	 * and rename it to "diskStructure->rock_ridge_move_count" (as a string)
	 */

	/* First see if the moved directory even exists */
	if (diskStructure->rr_moved_dir == NULL) {
		diskStructure->rr_moved_dir = cd9660_create_directory(
		    diskStructure, ISO_RRIP_DEFAULT_MOVE_DIR_NAME,
		    diskStructure->rootNode, dir);
		if (diskStructure->rr_moved_dir == NULL)
			return 0;
		cd9660_time_915(diskStructure->rr_moved_dir->isoDirRecord->date,
		    stampst.st_ino ? stampst.st_mtime : start_time.tv_sec);
	}

	/* Create a file with the same ORIGINAL name */
	tfile = cd9660_create_file(diskStructure, dir->node->name, dir->parent,
	    dir);
	if (tfile == NULL)
		return NULL;

	diskStructure->rock_ridge_move_count++;
	snprintf(newname, sizeof(newname), "%08i",
	    diskStructure->rock_ridge_move_count);

	/* Point to old parent */
	dir->rr_real_parent = dir->parent;

	/* Place the placeholder file */
	if (TAILQ_EMPTY(&dir->rr_real_parent->cn_children)) {
		TAILQ_INSERT_HEAD(&dir->rr_real_parent->cn_children, tfile,
		    cn_next_child);
	} else {
		cd9660_sorted_child_insert(dir->rr_real_parent, tfile);
	}

	/* Point to new parent */
	dir->parent = diskStructure->rr_moved_dir;

	/* Point the file to the moved directory */
	tfile->rr_relocated = dir;

	/* Actually move the directory */
	cd9660_sorted_child_insert(diskStructure->rr_moved_dir, dir);

	/* TODO: Inherit permissions / ownership (basically the entire inode) */

	/* Set the new name */
	memset(dir->isoDirRecord->name, 0, ISO_FILENAME_MAXLENGTH_WITH_PADDING);
	strncpy(dir->isoDirRecord->name, newname, 8);
	dir->isoDirRecord->length[0] = 34 + 8;
	dir->isoDirRecord->name_len[0] = 8;

	return dir;
}