#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct tac_handle {scalar_t__ fd; int num_servers; int single_connect; size_t cur_server; TYPE_1__* servers; } ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int TAC_SRVR_SINGLE_CONNECT ; 
 scalar_t__ conn_server (struct tac_handle*) ; 
 int /*<<< orphan*/  generr (struct tac_handle*,char*) ; 

__attribute__((used)) static int
establish_connection(struct tac_handle *h)
{
	int i;

	if (h->fd >= 0)		/* Already connected. */
		return 0;
	if (h->num_servers == 0) {
		generr(h, "No TACACS+ servers specified");
		return -1;
	}
	/*
         * Try the servers round-robin.  We begin with the one that
         * worked for us the last time.  That way, once we find a good
         * server, we won't waste any more time trying the bad ones.
	 */
	for (i = 0;  i < h->num_servers;  i++) {
		if (conn_server(h) == 0) {
			h->single_connect = (h->servers[h->cur_server].flags &
			    TAC_SRVR_SINGLE_CONNECT) != 0;
			return 0;
		}
		if (++h->cur_server >= h->num_servers)	/* Wrap around */
			h->cur_server = 0;
	}
	/* Just return whatever error was last reported by conn_server(). */
	return -1;
}