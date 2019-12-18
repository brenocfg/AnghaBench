#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int32_t ;
struct TYPE_6__ {TYPE_1__* copper_queue; } ;
typedef  TYPE_2__ ips_softc_t ;
struct TYPE_5__ {scalar_t__ nextstatus; scalar_t__ base_phys_addr; int /*<<< orphan*/ * status; } ;

/* Variables and functions */
 int /*<<< orphan*/  COPPER_REG_SQTR ; 
 scalar_t__ IPS_MAX_CMD_NUM ; 
 int /*<<< orphan*/  ips_write_4 (TYPE_2__*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static u_int32_t ips_copperhead_cmd_status(ips_softc_t *sc)
{
	u_int32_t value;
	int statnum = sc->copper_queue->nextstatus++;
	if(sc->copper_queue->nextstatus == IPS_MAX_CMD_NUM)
		sc->copper_queue->nextstatus = 0;
	value = sc->copper_queue->status[statnum];
	ips_write_4(sc, COPPER_REG_SQTR, sc->copper_queue->base_phys_addr + 
		    4 * statnum);
	return value;
}