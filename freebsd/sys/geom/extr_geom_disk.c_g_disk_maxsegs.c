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
struct disk {int dummy; } ;
struct bio {int dummy; } ;

/* Variables and functions */
 int PAGE_SIZE ; 
 int g_disk_maxsize (struct disk*,struct bio*) ; 

__attribute__((used)) static int
g_disk_maxsegs(struct disk *dp, struct bio *bp)
{
	return ((g_disk_maxsize(dp, bp) / PAGE_SIZE) + 1);
}