#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* sc_p ;
typedef  int /*<<< orphan*/  node_p ;
typedef  int /*<<< orphan*/  hook_p ;
struct TYPE_4__ {int /*<<< orphan*/  handle; int /*<<< orphan*/  seqRetries; int /*<<< orphan*/  remote_seq; int /*<<< orphan*/  local_seq; } ;

/* Variables and functions */
 int /*<<< orphan*/  CISCO_KEEPALIVE_REQ ; 
 int KEEPALIVE_SECS ; 
 int /*<<< orphan*/  NGM_LINK_IS_DOWN ; 
 int /*<<< orphan*/  cisco_notify (TYPE_1__* const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cisco_send (TYPE_1__* const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int hz ; 
 int /*<<< orphan*/  ng_callout (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,void (*) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int),void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
cisco_keepalive(node_p node, hook_p hook, void *arg1, int arg2)
{
	const sc_p sc = arg1;

	cisco_send(sc, CISCO_KEEPALIVE_REQ, sc->local_seq, sc->remote_seq);
	if (sc->seqRetries++ > 1)
		cisco_notify(sc, NGM_LINK_IS_DOWN);
	ng_callout(&sc->handle, node, NULL, (hz * KEEPALIVE_SECS),
	    &cisco_keepalive, (void *)sc, 0);
}