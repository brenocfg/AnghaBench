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
struct gdbcons {int npending; int /*<<< orphan*/ * buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  gdb_tx_begin (char) ; 
 int /*<<< orphan*/  gdb_tx_end () ; 
 int /*<<< orphan*/  gdb_tx_puthex (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
gdb_cnflush(void *arg)
{
	struct gdbcons *gc = arg;
	int i;

	gdb_tx_begin('O');
	for (i = 0; i < gc->npending; i++)
		gdb_tx_puthex(gc->buf[i]);
	gdb_tx_end();
	gc->npending = 0;
}