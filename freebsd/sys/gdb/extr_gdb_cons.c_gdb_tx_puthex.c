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
 int /*<<< orphan*/  gdb_tx_char (char const) ; 

__attribute__((used)) static void
gdb_tx_puthex(int c)
{
	const char *hex = "0123456789abcdef";

	gdb_tx_char(hex[(c>>4)&0xf]);
	gdb_tx_char(hex[(c>>0)&0xf]);
}