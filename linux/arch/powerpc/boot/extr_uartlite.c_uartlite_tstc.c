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
typedef  int u8 ;
typedef  int u32 ;

/* Variables and functions */
 scalar_t__ ULITE_STATUS ; 
 int ULITE_STATUS_RXVALID ; 
 int in_be32 (scalar_t__) ; 
 scalar_t__ reg_base ; 

__attribute__((used)) static u8 uartlite_tstc(void)
{
	u32 reg = in_be32(reg_base + ULITE_STATUS);
	return reg & ULITE_STATUS_RXVALID;
}