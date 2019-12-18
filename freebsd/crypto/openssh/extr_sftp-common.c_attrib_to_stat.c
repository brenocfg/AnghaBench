#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct stat {int /*<<< orphan*/  st_mtime; int /*<<< orphan*/  st_atime; int /*<<< orphan*/  st_mode; int /*<<< orphan*/  st_gid; int /*<<< orphan*/  st_uid; int /*<<< orphan*/  st_size; } ;
struct TYPE_3__ {int flags; int /*<<< orphan*/  mtime; int /*<<< orphan*/  atime; int /*<<< orphan*/  perm; int /*<<< orphan*/  gid; int /*<<< orphan*/  uid; int /*<<< orphan*/  size; } ;
typedef  TYPE_1__ Attrib ;

/* Variables and functions */
 int SSH2_FILEXFER_ATTR_ACMODTIME ; 
 int SSH2_FILEXFER_ATTR_PERMISSIONS ; 
 int SSH2_FILEXFER_ATTR_SIZE ; 
 int SSH2_FILEXFER_ATTR_UIDGID ; 
 int /*<<< orphan*/  memset (struct stat*,int /*<<< orphan*/ ,int) ; 

void
attrib_to_stat(const Attrib *a, struct stat *st)
{
	memset(st, 0, sizeof(*st));

	if (a->flags & SSH2_FILEXFER_ATTR_SIZE)
		st->st_size = a->size;
	if (a->flags & SSH2_FILEXFER_ATTR_UIDGID) {
		st->st_uid = a->uid;
		st->st_gid = a->gid;
	}
	if (a->flags & SSH2_FILEXFER_ATTR_PERMISSIONS)
		st->st_mode = a->perm;
	if (a->flags & SSH2_FILEXFER_ATTR_ACMODTIME) {
		st->st_atime = a->atime;
		st->st_mtime = a->mtime;
	}
}