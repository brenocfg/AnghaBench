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
 unsigned int NUM_GPRS ; 
 char const** gpr_names ; 

const char *regs_query_register_name(unsigned int offset)
{
	if (offset >= NUM_GPRS)
		return NULL;
	return gpr_names[offset];
}