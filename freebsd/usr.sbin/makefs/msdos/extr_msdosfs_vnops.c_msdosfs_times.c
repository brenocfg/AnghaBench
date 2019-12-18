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
struct stat {int /*<<< orphan*/  st_mtim; int /*<<< orphan*/  st_atim; int /*<<< orphan*/  st_birthtim; scalar_t__ st_ino; } ;
struct denode {int /*<<< orphan*/  de_MTime; int /*<<< orphan*/  de_MDate; int /*<<< orphan*/  de_ADate; int /*<<< orphan*/  de_CTime; int /*<<< orphan*/  de_CDate; } ;

/* Variables and functions */
 struct stat stampst ; 
 int /*<<< orphan*/  unix2fattime (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
msdosfs_times(struct denode *dep, const struct stat *st)
{
	if (stampst.st_ino)
		st = &stampst;

	unix2fattime(&st->st_birthtim, &dep->de_CDate, &dep->de_CTime);
	unix2fattime(&st->st_atim, &dep->de_ADate, NULL);
	unix2fattime(&st->st_mtim, &dep->de_MDate, &dep->de_MTime);
}