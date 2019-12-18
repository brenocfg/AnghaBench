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
struct mtd_partition {unsigned int offset; unsigned int size; } ;

/* Variables and functions */
 unsigned int AC49X_FLASH_ADDRMASK ; 
 unsigned int sscanf (unsigned char const*,char*,unsigned int*,unsigned int*) ; 

int parse_partvar(const unsigned char *partvar, struct mtd_partition *part)
{
	unsigned int partstart, partend;
	unsigned int pnum;

	pnum = sscanf(partvar, "0x%x,0x%x", &partstart, &partend);
	if (pnum != 2)
		return 1;

	part->offset = partstart & AC49X_FLASH_ADDRMASK;
	part->size = partend - partstart;

	return 0;
}