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
 int DR_CONTROL_SHIFT ; 
 int DR_CONTROL_SIZE ; 
 int DR_ENABLE_SIZE ; 
 int DR_GLOBAL_ENABLE ; 

__attribute__((used)) static inline unsigned long
__encode_dr7(int drnum, unsigned int len, unsigned int type)
{
	unsigned long bp_info;

	bp_info = (len | type) & 0xf;
	bp_info <<= (DR_CONTROL_SHIFT + drnum * DR_CONTROL_SIZE);
	bp_info |= (DR_GLOBAL_ENABLE << (drnum * DR_ENABLE_SIZE));

	return bp_info;
}