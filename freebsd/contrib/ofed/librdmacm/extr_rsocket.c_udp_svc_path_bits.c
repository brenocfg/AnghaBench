#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct ibv_port_attr {int lmc; } ;
struct ds_dest {TYPE_2__* qp; } ;
struct TYPE_4__ {TYPE_1__* cm_id; } ;
struct TYPE_3__ {int /*<<< orphan*/  port_num; int /*<<< orphan*/  verbs; } ;

/* Variables and functions */
 int /*<<< orphan*/  ibv_query_port (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ibv_port_attr*) ; 

__attribute__((used)) static uint8_t udp_svc_path_bits(struct ds_dest *dest)
{
	struct ibv_port_attr attr;

	if (!ibv_query_port(dest->qp->cm_id->verbs, dest->qp->cm_id->port_num, &attr))
		return (uint8_t) ((1 << attr.lmc) - 1);
	return 0x7f;
}