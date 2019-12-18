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
 int /*<<< orphan*/  DIAG_STAT_X204 ; 
 unsigned long __diag204 (unsigned long*,unsigned long,void*) ; 
 int /*<<< orphan*/  diag_stat_inc (int /*<<< orphan*/ ) ; 

int diag204(unsigned long subcode, unsigned long size, void *addr)
{
	diag_stat_inc(DIAG_STAT_X204);
	size = __diag204(&subcode, size, addr);
	if (subcode)
		return -1;
	return size;
}