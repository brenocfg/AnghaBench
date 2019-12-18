#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int uint32_t ;
struct TYPE_5__ {scalar_t__ targ; scalar_t__ init; TYPE_1__* sport; } ;
typedef  TYPE_2__ ocs_node_t ;
typedef  int /*<<< orphan*/  ocs_node_enable_e ;
struct TYPE_4__ {scalar_t__ enable_tgt; scalar_t__ enable_ini; } ;

/* Variables and functions */

__attribute__((used)) static inline ocs_node_enable_e ocs_node_get_enable(ocs_node_t *node)
{
	uint32_t retval = 0;

	if (node->sport->enable_ini) retval |= (1U << 3);
	if (node->sport->enable_tgt) retval |= (1U << 2);
	if (node->init) retval |= (1U << 1);
	if (node->targ) retval |= (1U << 0);
	return (ocs_node_enable_e) retval;
}