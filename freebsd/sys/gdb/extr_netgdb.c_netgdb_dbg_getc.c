#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int (* gdb_getc ) () ;} ;
struct TYPE_5__ {int* s_buf; } ;

/* Variables and functions */
 int CTRL (char) ; 
 int /*<<< orphan*/  debugnet_network_poll (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netgdb_conn ; 
 int /*<<< orphan*/  netgdb_fini () ; 
 TYPE_4__* netgdb_prev_dbgport ; 
 size_t netgdb_rx_off ; 
 TYPE_1__ netgdb_rxsb ; 
 int /*<<< orphan*/  sbuf_clear (TYPE_1__*) ; 
 size_t sbuf_len (TYPE_1__*) ; 
 int stub1 () ; 

__attribute__((used)) static int
netgdb_dbg_getc(void)
{
	int c;

	while (true) {
		/* Pull bytes off any currently cached packet first. */
		if (netgdb_rx_off < sbuf_len(&netgdb_rxsb)) {
			c = netgdb_rxsb.s_buf[netgdb_rx_off];
			netgdb_rx_off++;
			break;
		}

		/* Reached EOF?  Reuse buffer. */
		sbuf_clear(&netgdb_rxsb);
		netgdb_rx_off = 0;

		/* Check for CTRL-C on console/serial, if any. */
		if (netgdb_prev_dbgport != NULL) {
			c = netgdb_prev_dbgport->gdb_getc();
			if (c == CTRL('C'))
				break;
		}

		debugnet_network_poll(netgdb_conn);
	}

	if (c == CTRL('C')) {
		netgdb_fini();
		/* Caller gdb_getc() will print that we got ^C. */
	}
	return (c);
}