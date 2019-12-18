#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct stat {int st_mode; scalar_t__ st_size; int /*<<< orphan*/  st_gid; int /*<<< orphan*/  st_uid; int /*<<< orphan*/  st_ino; int /*<<< orphan*/  st_rdev; int /*<<< orphan*/  st_ctime_nsec; int /*<<< orphan*/  st_mtime_nsec; scalar_t__ st_mtime; scalar_t__ st_ctime; } ;
typedef  void* int32_t ;
struct TYPE_6__ {int /*<<< orphan*/  nanoseconds; void* seconds; } ;
struct TYPE_5__ {int /*<<< orphan*/  nanoseconds; void* seconds; } ;
struct TYPE_7__ {scalar_t__ file_size; int /*<<< orphan*/  gid; int /*<<< orphan*/  uid; int /*<<< orphan*/  mode; int /*<<< orphan*/  ino; int /*<<< orphan*/  dev; TYPE_2__ ctime; TYPE_1__ mtime; } ;
typedef  TYPE_3__ git_index_entry ;

/* Variables and functions */
 scalar_t__ S_ISREG (int) ; 
 int /*<<< orphan*/  git_index__create_mode (int) ; 

void git_index_entry__init_from_stat(
	git_index_entry *entry, struct stat *st, bool trust_mode)
{
	entry->ctime.seconds = (int32_t)st->st_ctime;
	entry->mtime.seconds = (int32_t)st->st_mtime;
#if defined(GIT_USE_NSEC)
	entry->mtime.nanoseconds = st->st_mtime_nsec;
	entry->ctime.nanoseconds = st->st_ctime_nsec;
#endif
	entry->dev  = st->st_rdev;
	entry->ino  = st->st_ino;
	entry->mode = (!trust_mode && S_ISREG(st->st_mode)) ?
		git_index__create_mode(0666) : git_index__create_mode(st->st_mode);
	entry->uid  = st->st_uid;
	entry->gid  = st->st_gid;
	entry->file_size = (uint32_t)st->st_size;
}