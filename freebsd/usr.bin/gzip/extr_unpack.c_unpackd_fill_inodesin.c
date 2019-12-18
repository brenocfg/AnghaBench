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
struct TYPE_3__ {int treelevels; int* inodesin; int* symbolsin; } ;
typedef  TYPE_1__ unpack_descriptor_t ;

/* Variables and functions */

__attribute__((used)) static void
unpackd_fill_inodesin(const unpack_descriptor_t *unpackd, int level)
{

	/*
	 * The internal nodes would be 1/2 of total internal nodes and
	 * leaf nodes in the next level.  For the last level there
	 * would be no internal node by definition.
	 */
	if (level < unpackd->treelevels) {
		unpackd_fill_inodesin(unpackd, level + 1);
		unpackd->inodesin[level] = (unpackd->inodesin[level + 1] +
		    unpackd->symbolsin[level + 1]) / 2;
	} else
		unpackd->inodesin[level] = 0;
}