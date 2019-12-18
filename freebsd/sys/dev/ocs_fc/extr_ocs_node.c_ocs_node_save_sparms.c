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
struct TYPE_3__ {int /*<<< orphan*/  service_params; } ;
typedef  TYPE_1__ ocs_node_t ;

/* Variables and functions */
 int /*<<< orphan*/  ocs_memcpy (int /*<<< orphan*/ ,void*,int) ; 

void
ocs_node_save_sparms(ocs_node_t *node, void *payload)
{
	ocs_memcpy(node->service_params, payload, sizeof(node->service_params));
}