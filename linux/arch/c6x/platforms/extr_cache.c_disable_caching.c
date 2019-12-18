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

/* Variables and functions */
 unsigned long IMCR_MAR_BASE ; 
 int imcr_get (unsigned int) ; 
 int /*<<< orphan*/  imcr_set (unsigned int,int) ; 

void disable_caching(unsigned long start, unsigned long end)
{
	unsigned int mar = IMCR_MAR_BASE + ((start >> 24) << 2);
	unsigned int mar_e = IMCR_MAR_BASE + ((end >> 24) << 2);

	for (; mar <= mar_e; mar += 4)
		imcr_set(mar, imcr_get(mar) & ~1);
}