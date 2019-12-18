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
 int /*<<< orphan*/  do_qXfer_threads_read () ; 
 int /*<<< orphan*/  gdb_rx_equal (char*) ; 
 int /*<<< orphan*/  gdb_tx_empty () ; 

__attribute__((used)) static void
do_qXfer(void)
{
	if (!gdb_rx_equal("threads:"))
		goto unrecognized;

	if (!gdb_rx_equal("read:"))
		goto unrecognized;

	do_qXfer_threads_read();
	return;

unrecognized:
	gdb_tx_empty();
	return;
}