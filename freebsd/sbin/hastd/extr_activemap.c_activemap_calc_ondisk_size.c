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
typedef  int uint64_t ;
typedef  int uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  PJDLOG_ASSERT (int) ; 
 int bitstr_size (int) ; 
 int powerof2 (int) ; 
 size_t roundup2 (int,int) ; 

size_t
activemap_calc_ondisk_size(uint64_t mediasize, uint32_t extentsize,
    uint32_t sectorsize)
{
	uint64_t nextents, mapsize;

	PJDLOG_ASSERT(mediasize > 0);
	PJDLOG_ASSERT(extentsize > 0);
	PJDLOG_ASSERT(powerof2(extentsize));
	PJDLOG_ASSERT(sectorsize > 0);
	PJDLOG_ASSERT(powerof2(sectorsize));

	nextents = ((mediasize - 1) / extentsize) + 1;
	mapsize = bitstr_size(nextents);
	return (roundup2(mapsize, sectorsize));
}