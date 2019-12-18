#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_6__* sc_p ;
typedef  int /*<<< orphan*/  node_p ;
struct TYPE_12__ {int /*<<< orphan*/  af; } ;
struct TYPE_11__ {int /*<<< orphan*/  af; } ;
struct TYPE_10__ {int /*<<< orphan*/  af; } ;
struct TYPE_9__ {int /*<<< orphan*/  af; } ;
struct TYPE_13__ {int af; } ;
struct TYPE_14__ {TYPE_4__ ipx; TYPE_3__ atalk; TYPE_2__ inet6; TYPE_1__ inet; TYPE_5__ downstream; int /*<<< orphan*/  node; int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_APPLETALK ; 
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  AF_INET6 ; 
 int /*<<< orphan*/  AF_IPX ; 
 int /*<<< orphan*/  M_NETGRAPH ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  NG_NODE_SET_PRIVATE (int /*<<< orphan*/ ,TYPE_6__*) ; 
 TYPE_6__* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ng_callout_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
cisco_constructor(node_p node)
{
	sc_p sc;

	sc = malloc(sizeof(*sc), M_NETGRAPH, M_WAITOK | M_ZERO);

	ng_callout_init(&sc->handle);
	NG_NODE_SET_PRIVATE(node, sc);
	sc->node = node;

	/* Initialise the varous protocol hook holders */
	sc->downstream.af = 0xffff;
	sc->inet.af = AF_INET;
	sc->inet6.af = AF_INET6;
	sc->atalk.af = AF_APPLETALK;
	sc->ipx.af = AF_IPX;
	return (0);
}