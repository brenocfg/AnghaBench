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
struct mpt_drive_list {int ndrives; TYPE_1__** drives; } ;
typedef  scalar_t__ U8 ;
struct TYPE_2__ {scalar_t__ PhysDiskNum; } ;

/* Variables and functions */
 int errno ; 
 TYPE_1__* mpt_pd_info (int,scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
mpt_pd_insert(int fd, struct mpt_drive_list *list, U8 PhysDiskNum)
{
	int i, j;

	/*
	 * First, do a simple linear search to see if we have already
	 * seen this drive.
	 */
	for (i = 0; i < list->ndrives; i++) {
		if (list->drives[i]->PhysDiskNum == PhysDiskNum)
			return (0);
		if (list->drives[i]->PhysDiskNum > PhysDiskNum)
			break;
	}

	/*
	 * 'i' is our slot for the 'new' drive.  Make room and then
	 * read the drive info.
	 */
	for (j = list->ndrives - 1; j >= i; j--)
		list->drives[j + 1] = list->drives[j];
	list->drives[i] = mpt_pd_info(fd, PhysDiskNum, NULL);
	if (list->drives[i] == NULL)
		return (errno);
	list->ndrives++;
	return (0);
}