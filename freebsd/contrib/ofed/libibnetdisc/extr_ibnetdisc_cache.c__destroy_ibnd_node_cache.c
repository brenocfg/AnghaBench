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
struct TYPE_4__ {scalar_t__ node; int /*<<< orphan*/  node_stored_to_fabric; struct TYPE_4__* port_cache_keys; } ;
typedef  TYPE_1__ ibnd_node_cache_t ;

/* Variables and functions */
 int /*<<< orphan*/  destroy_node (scalar_t__) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 

__attribute__((used)) static void _destroy_ibnd_node_cache(ibnd_node_cache_t * node_cache)
{
	free(node_cache->port_cache_keys);
	if (!node_cache->node_stored_to_fabric && node_cache->node)
		destroy_node(node_cache->node);
	free(node_cache);
}