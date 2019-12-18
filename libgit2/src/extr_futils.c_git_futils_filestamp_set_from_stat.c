#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct stat {scalar_t__ st_ino; scalar_t__ st_size; scalar_t__ st_mtime_nsec; int /*<<< orphan*/  st_mtime; } ;
typedef  scalar_t__ git_off_t ;
struct TYPE_5__ {scalar_t__ tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct TYPE_6__ {unsigned int ino; scalar_t__ size; TYPE_1__ mtime; } ;
typedef  TYPE_2__ git_futils_filestamp ;

/* Variables and functions */
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

void git_futils_filestamp_set_from_stat(
	git_futils_filestamp *stamp, struct stat *st)
{
	if (st) {
		stamp->mtime.tv_sec = st->st_mtime;
#if defined(GIT_USE_NSEC)
		stamp->mtime.tv_nsec = st->st_mtime_nsec;
#else
		stamp->mtime.tv_nsec = 0;
#endif
		stamp->size  = (git_off_t)st->st_size;
		stamp->ino   = (unsigned int)st->st_ino;
	} else {
		memset(stamp, 0, sizeof(*stamp));
	}
}