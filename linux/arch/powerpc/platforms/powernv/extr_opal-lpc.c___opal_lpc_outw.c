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
typedef  int __le16 ;

/* Variables and functions */
 int /*<<< orphan*/  OPAL_LPC_IO ; 
 scalar_t__ opal_lpc_chip_id ; 
 int /*<<< orphan*/  opal_lpc_outb (int,unsigned long) ; 
 int /*<<< orphan*/  opal_lpc_write (scalar_t__,int /*<<< orphan*/ ,unsigned long,int,int) ; 

__attribute__((used)) static void __opal_lpc_outw(__le16 val, unsigned long port)
{
	if (opal_lpc_chip_id < 0 || port > 0xfffe)
		return;
	if (port & 1) {
		opal_lpc_outb(val >> 8, port);
		opal_lpc_outb(val     , port + 1);
		return;
	}
	opal_lpc_write(opal_lpc_chip_id, OPAL_LPC_IO, port, val, 2);
}