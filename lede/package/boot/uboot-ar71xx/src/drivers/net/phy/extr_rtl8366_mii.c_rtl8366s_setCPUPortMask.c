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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  RTL8366S_CPU_CTRL_REG ; 
 int /*<<< orphan*/  printf (char*) ; 
 int rtl8366_setRegisterBit (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

int rtl8366s_setCPUPortMask(uint8_t port, uint32_t enabled)
{
	if(port >= 6){
		printf("rtl8366s_setCPUPortMask: invalid port number\n");
		return -1;
	}

	return rtl8366_setRegisterBit(RTL8366S_CPU_CTRL_REG, port, enabled);
}