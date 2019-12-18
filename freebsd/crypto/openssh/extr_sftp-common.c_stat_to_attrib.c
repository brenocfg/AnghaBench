#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct stat {int /*<<< orphan*/  st_mtime; int /*<<< orphan*/  st_atime; int /*<<< orphan*/  st_mode; int /*<<< orphan*/  st_gid; int /*<<< orphan*/  st_uid; int /*<<< orphan*/  st_size; } ;
struct TYPE_4__ {int /*<<< orphan*/  mtime; int /*<<< orphan*/  atime; int /*<<< orphan*/  flags; int /*<<< orphan*/  perm; int /*<<< orphan*/  gid; int /*<<< orphan*/  uid; int /*<<< orphan*/  size; } ;
typedef  TYPE_1__ Attrib ;

/* Variables and functions */
 int /*<<< orphan*/  SSH2_FILEXFER_ATTR_ACMODTIME ; 
 int /*<<< orphan*/  SSH2_FILEXFER_ATTR_PERMISSIONS ; 
 int /*<<< orphan*/  SSH2_FILEXFER_ATTR_SIZE ; 
 int /*<<< orphan*/  SSH2_FILEXFER_ATTR_UIDGID ; 
 int /*<<< orphan*/  attrib_clear (TYPE_1__*) ; 

void
stat_to_attrib(const struct stat *st, Attrib *a)
{
	attrib_clear(a);
	a->flags = 0;
	a->flags |= SSH2_FILEXFER_ATTR_SIZE;
	a->size = st->st_size;
	a->flags |= SSH2_FILEXFER_ATTR_UIDGID;
	a->uid = st->st_uid;
	a->gid = st->st_gid;
	a->flags |= SSH2_FILEXFER_ATTR_PERMISSIONS;
	a->perm = st->st_mode;
	a->flags |= SSH2_FILEXFER_ATTR_ACMODTIME;
	a->atime = st->st_atime;
	a->mtime = st->st_mtime;
}