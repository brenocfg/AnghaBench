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
 int NO_XP ; 
 int PERPAGE_XP ; 
 scalar_t__ system (char*) ; 

int
exec_prot_support(void)
{
	if (system("cpuctl identify 0 | grep -q NOX") == 0 ||
	    system("cpuctl identify 0 | grep -q XD") == 0)
		return PERPAGE_XP;
	
	return NO_XP;
}