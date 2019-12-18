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
struct TYPE_2__ {int /*<<< orphan*/  f_mntfromname; } ;
struct mount {TYPE_1__ mnt_stat; } ;

/* Variables and functions */
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const*,int) ; 

void
vfs_mountedfrom(struct mount *mp, const char *from)
{

	bzero(mp->mnt_stat.f_mntfromname, sizeof mp->mnt_stat.f_mntfromname);
	strlcpy(mp->mnt_stat.f_mntfromname, from,
	    sizeof mp->mnt_stat.f_mntfromname);
}