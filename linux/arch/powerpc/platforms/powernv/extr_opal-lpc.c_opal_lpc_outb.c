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
typedef  int /*<<< orphan*/  u8 ;

/* Variables and functions */
 int /*<<< orphan*/  OPAL_LPC_IO ; 
 scalar_t__ opal_lpc_chip_id ; 
 int /*<<< orphan*/  opal_lpc_write (scalar_t__,int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void opal_lpc_outb(u8 val, unsigned long port)
{
	if (opal_lpc_chip_id < 0 || port > 0xffff)
		return;
	opal_lpc_write(opal_lpc_chip_id, OPAL_LPC_IO, port, val, 1);
}