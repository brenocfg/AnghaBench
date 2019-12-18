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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  smp_engine_t ;
typedef  int /*<<< orphan*/  ibnd_smp_t ;
struct TYPE_2__ {int /*<<< orphan*/  nodedesc; } ;
typedef  TYPE_1__ ibnd_node_t ;

/* Variables and functions */
 int IB_SMP_DATA_OFFS ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int recv_node_desc(smp_engine_t * engine, ibnd_smp_t * smp,
			  uint8_t * mad, void *cb_data)
{
	uint8_t *node_desc = mad + IB_SMP_DATA_OFFS;
	ibnd_node_t *node = cb_data;
	memcpy(node->nodedesc, node_desc, sizeof(node->nodedesc));
	return 0;
}