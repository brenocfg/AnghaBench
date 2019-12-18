#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct rtentry {int dummy; } ;
struct TYPE_4__ {struct rtentry* ro_rt; } ;
struct inpcb {TYPE_2__* inp_socket; TYPE_1__ inp_route; } ;
struct TYPE_5__ {int so_error; } ;

/* Variables and functions */
 int EHOSTDOWN ; 
 int EHOSTUNREACH ; 
 int ENETUNREACH ; 
 int /*<<< orphan*/  INP_WLOCK_ASSERT (struct inpcb*) ; 
 int /*<<< orphan*/  RTFREE (struct rtentry*) ; 
 int /*<<< orphan*/  sorwakeup (TYPE_2__*) ; 
 int /*<<< orphan*/  sowwakeup (TYPE_2__*) ; 

struct inpcb *
udp_notify(struct inpcb *inp, int errno)
{

	INP_WLOCK_ASSERT(inp);
	if ((errno == EHOSTUNREACH || errno == ENETUNREACH ||
	     errno == EHOSTDOWN) && inp->inp_route.ro_rt) {
		RTFREE(inp->inp_route.ro_rt);
		inp->inp_route.ro_rt = (struct rtentry *)NULL;
	}

	inp->inp_socket->so_error = errno;
	sorwakeup(inp->inp_socket);
	sowwakeup(inp->inp_socket);
	return (inp);
}