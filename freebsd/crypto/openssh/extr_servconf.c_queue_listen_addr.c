#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct queued_listenaddr {int port; int /*<<< orphan*/ * rdomain; int /*<<< orphan*/ * addr; } ;
struct TYPE_3__ {scalar_t__ num_queued_listens; struct queued_listenaddr* queued_listen_addrs; } ;
typedef  TYPE_1__ ServerOptions ;

/* Variables and functions */
 struct queued_listenaddr* xrecallocarray (struct queued_listenaddr*,scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/ * xstrdup (char const*) ; 

__attribute__((used)) static void
queue_listen_addr(ServerOptions *options, const char *addr,
    const char *rdomain, int port)
{
	struct queued_listenaddr *qla;

	options->queued_listen_addrs = xrecallocarray(
	    options->queued_listen_addrs,
	    options->num_queued_listens, options->num_queued_listens + 1,
	    sizeof(*options->queued_listen_addrs));
	qla = &options->queued_listen_addrs[options->num_queued_listens++];
	qla->addr = xstrdup(addr);
	qla->port = port;
	qla->rdomain = rdomain == NULL ? NULL : xstrdup(rdomain);
}