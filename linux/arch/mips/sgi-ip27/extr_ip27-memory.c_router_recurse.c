#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ brd_type; int /*<<< orphan*/ * brd_compts; } ;
typedef  TYPE_2__ lboard_t ;
struct TYPE_9__ {int rou_rflag; TYPE_1__* rou_port; } ;
typedef  TYPE_3__ klrou_t ;
struct TYPE_7__ {scalar_t__ port_nasid; int /*<<< orphan*/  port_offset; } ;

/* Variables and functions */
 scalar_t__ INVALID_NASID ; 
 scalar_t__ KLTYPE_ROUTER ; 
 int MAX_ROUTER_PORTS ; 
 scalar_t__ NASID_GET (TYPE_2__*) ; 
 scalar_t__ NODE_OFFSET_TO_K0 (scalar_t__,int /*<<< orphan*/ ) ; 
 int router_distance ; 

__attribute__((used)) static void router_recurse(klrou_t *router_a, klrou_t *router_b, int depth)
{
	klrou_t *router;
	lboard_t *brd;
	int	port;

	if (router_a->rou_rflag == 1)
		return;

	if (depth >= router_distance)
		return;

	router_a->rou_rflag = 1;

	for (port = 1; port <= MAX_ROUTER_PORTS; port++) {
		if (router_a->rou_port[port].port_nasid == INVALID_NASID)
			continue;

		brd = (lboard_t *)NODE_OFFSET_TO_K0(
			router_a->rou_port[port].port_nasid,
			router_a->rou_port[port].port_offset);

		if (brd->brd_type == KLTYPE_ROUTER) {
			router = (klrou_t *)NODE_OFFSET_TO_K0(NASID_GET(brd), brd->brd_compts[0]);
			if (router == router_b) {
				if (depth < router_distance)
					router_distance = depth;
			}
			else
				router_recurse(router, router_b, depth + 1);
		}
	}

	router_a->rou_rflag = 0;
}