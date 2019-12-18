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
typedef  int uint16_t ;
struct TYPE_4__ {int base_lid; int lmc; } ;
typedef  TYPE_1__ ibnd_port_t ;
typedef  int /*<<< orphan*/  GHashTable ;

/* Variables and functions */
 int /*<<< orphan*/  GINT_TO_POINTER (int) ; 
 int /*<<< orphan*/  g_hash_table_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 

void add_to_portlid_hash(ibnd_port_t * port, GHashTable *htable)
{
	uint16_t base_lid = port->base_lid;
	uint16_t lid_mask = ((1 << port->lmc) -1);
	uint16_t lid = 0;
	/* 0 < valid lid <= 0xbfff */
	if (base_lid > 0 && base_lid <= 0xbfff) {
		/* We add the port for all lids
		 * so it is easier to find any "random" lid specified */
		for (lid = base_lid; lid <= (base_lid + lid_mask); lid++) {
			g_hash_table_insert(htable, GINT_TO_POINTER(lid), port);
		}
	}
}