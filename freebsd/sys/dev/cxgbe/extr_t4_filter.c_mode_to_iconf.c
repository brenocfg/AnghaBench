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
typedef  int uint32_t ;

/* Variables and functions */
 int F_VNIC ; 
 int T4_FILTER_IC_VNIC ; 

__attribute__((used)) static uint32_t
mode_to_iconf(uint32_t mode)
{

	if (mode & T4_FILTER_IC_VNIC)
		return (F_VNIC);
	return (0);
}