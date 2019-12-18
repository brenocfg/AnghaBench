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
typedef  int u32 ;

/* Variables and functions */
 scalar_t__ ULITE_STATUS ; 
 int ULITE_STATUS_TXFULL ; 
 scalar_t__ ULITE_TX ; 
 int in_be32 (scalar_t__) ; 
 int /*<<< orphan*/  out_be32 (scalar_t__,unsigned char) ; 
 scalar_t__ reg_base ; 

__attribute__((used)) static void uartlite_putc(unsigned char c)
{
	u32 reg = ULITE_STATUS_TXFULL;
	while (reg & ULITE_STATUS_TXFULL) /* spin on TXFULL bit */
		reg = in_be32(reg_base + ULITE_STATUS);
	out_be32(reg_base + ULITE_TX, c);
}