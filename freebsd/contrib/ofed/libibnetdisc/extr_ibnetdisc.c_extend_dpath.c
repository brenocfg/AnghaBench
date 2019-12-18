#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;
typedef  struct TYPE_12__   TYPE_11__ ;

/* Type definitions */
typedef  scalar_t__ uint16_t ;
struct TYPE_16__ {TYPE_5__* user_data; } ;
typedef  TYPE_4__ smp_engine_t ;
struct TYPE_14__ {scalar_t__ lid; } ;
struct TYPE_17__ {unsigned int initial_hops; TYPE_2__ selfportid; TYPE_1__* cfg; TYPE_7__* f_int; } ;
typedef  TYPE_5__ ibnd_scan_t ;
struct TYPE_12__ {int drdlid; scalar_t__ cnt; scalar_t__ drslid; } ;
struct TYPE_18__ {TYPE_11__ drpath; scalar_t__ lid; } ;
typedef  TYPE_6__ ib_portid_t ;
struct TYPE_15__ {scalar_t__ maxhops_discovered; } ;
struct TYPE_19__ {TYPE_3__ fabric; } ;
typedef  TYPE_7__ f_internal_t ;
struct TYPE_13__ {scalar_t__ max_hops; } ;

/* Variables and functions */
 int /*<<< orphan*/  IBND_ERROR (char*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ add_port_to_dpath (TYPE_11__*,int) ; 
 int /*<<< orphan*/  portid2str (TYPE_6__*) ; 

__attribute__((used)) static int extend_dpath(smp_engine_t * engine, ib_portid_t * portid,
			int nextport)
{
	ibnd_scan_t *scan = engine->user_data;
	f_internal_t *f_int = scan->f_int;

	if (scan->cfg->max_hops &&
	    f_int->fabric.maxhops_discovered > scan->cfg->max_hops)
		return 0;

	if (portid->lid) {
		/* If we were LID routed we need to set up the drslid */
		portid->drpath.drslid = (uint16_t) scan->selfportid.lid;
		portid->drpath.drdlid = 0xFFFF;
	}

	if (add_port_to_dpath(&portid->drpath, nextport) < 0) {
		IBND_ERROR("add port %d to DR path failed; %s\n", nextport,
			   portid2str(portid));
		return -1;
	}

	if (((unsigned) portid->drpath.cnt - scan->initial_hops) >
	    f_int->fabric.maxhops_discovered)
		f_int->fabric.maxhops_discovered++;

	return 1;
}