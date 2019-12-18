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
 int /*<<< orphan*/  gdb_tx_char (char) ; 
 int /*<<< orphan*/  gdb_txbuf ; 
 int /*<<< orphan*/  gdb_txp ; 

void
gdb_tx_begin(char tp)
{

	gdb_txp = gdb_txbuf;
	if (tp != '\0')
		gdb_tx_char(tp);
}