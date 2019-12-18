#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  smp_engine_t ;
struct TYPE_6__ {int /*<<< orphan*/  path; } ;
typedef  TYPE_1__ ibnd_smp_t ;
struct TYPE_7__ {int numports; } ;
typedef  TYPE_2__ ibnd_node_t ;

/* Variables and functions */
 int /*<<< orphan*/  query_port_info (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*,int) ; 
 int recv_port_info (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,void*) ; 

__attribute__((used)) static int recv_port0_info(smp_engine_t * engine, ibnd_smp_t * smp,
			   uint8_t * mad, void *cb_data)
{
	ibnd_node_t *node = cb_data;
	int i, status;

	status = recv_port_info(engine, smp, mad, cb_data);
	/* Query PortInfo on switch external/physical ports */
	for (i = 1; i <= node->numports; i++)
		query_port_info(engine, &smp->path, node, i);

	return status;
}