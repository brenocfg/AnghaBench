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
 scalar_t__ ULITE_CONTROL ; 
 int /*<<< orphan*/  ULITE_CONTROL_RST_RX ; 
 int /*<<< orphan*/  out_be32 (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ reg_base ; 

__attribute__((used)) static int uartlite_open(void)
{
	/* Clear the RX FIFO */
	out_be32(reg_base + ULITE_CONTROL, ULITE_CONTROL_RST_RX);
	return 0;
}