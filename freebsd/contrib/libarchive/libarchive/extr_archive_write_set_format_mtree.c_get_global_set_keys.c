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
struct TYPE_2__ {int keys; scalar_t__ gid; scalar_t__ uid; scalar_t__ fflags_set; scalar_t__ fflags_clear; scalar_t__ mode; int const type; } ;
struct mtree_writer {int keys; TYPE_1__ set; } ;
struct mtree_entry {scalar_t__ gid; scalar_t__ uid; scalar_t__ fflags_set; scalar_t__ fflags_clear; scalar_t__ mode; int filetype; } ;

/* Variables and functions */
#define  AE_IFBLK 134 
#define  AE_IFCHR 133 
#define  AE_IFDIR 132 
#define  AE_IFIFO 131 
#define  AE_IFLNK 130 
#define  AE_IFREG 129 
#define  AE_IFSOCK 128 
 int F_FLAGS ; 
 int F_GID ; 
 int F_GNAME ; 
 int F_MODE ; 
 int F_TYPE ; 
 int F_UID ; 
 int F_UNAME ; 

__attribute__((used)) static int
get_global_set_keys(struct mtree_writer *mtree, struct mtree_entry *me)
{
	int keys;

	keys = mtree->keys;

	/*
	 * If a keyword has been set by /set, we do not need to
	 * output it.
	 */
	if (mtree->set.keys == 0)
		return (keys);/* /set is not used. */

	if ((mtree->set.keys & (F_GNAME | F_GID)) != 0 &&
	     mtree->set.gid == me->gid)
		keys &= ~(F_GNAME | F_GID);
	if ((mtree->set.keys & (F_UNAME | F_UID)) != 0 &&
	     mtree->set.uid == me->uid)
		keys &= ~(F_UNAME | F_UID);
	if (mtree->set.keys & F_FLAGS) {
		if (mtree->set.fflags_set == me->fflags_set &&
		    mtree->set.fflags_clear == me->fflags_clear)
			keys &= ~F_FLAGS;
	}
	if ((mtree->set.keys & F_MODE) != 0 && mtree->set.mode == me->mode)
		keys &= ~F_MODE;

	switch (me->filetype) {
	case AE_IFLNK: case AE_IFSOCK: case AE_IFCHR:
	case AE_IFBLK: case AE_IFIFO:
		break;
	case AE_IFDIR:
		if ((mtree->set.keys & F_TYPE) != 0 &&
		    mtree->set.type == AE_IFDIR)
			keys &= ~F_TYPE;
		break;
	case AE_IFREG:
	default:	/* Handle unknown file types as regular files. */
		if ((mtree->set.keys & F_TYPE) != 0 &&
		    mtree->set.type == AE_IFREG)
			keys &= ~F_TYPE;
		break;
	}

	return (keys);
}