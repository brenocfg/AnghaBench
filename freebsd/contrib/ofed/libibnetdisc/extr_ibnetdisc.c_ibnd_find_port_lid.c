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
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  ibnd_port_t ;
typedef  int /*<<< orphan*/  ibnd_fabric_t ;
struct TYPE_2__ {int /*<<< orphan*/  lid2guid; } ;
typedef  TYPE_1__ f_internal_t ;

/* Variables and functions */
 int /*<<< orphan*/  GINT_TO_POINTER (int /*<<< orphan*/ ) ; 
 scalar_t__ g_hash_table_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

ibnd_port_t *ibnd_find_port_lid(ibnd_fabric_t * fabric,
				uint16_t lid)
{
	ibnd_port_t *port;
	f_internal_t *f = (f_internal_t *)fabric;

	port = (ibnd_port_t *)g_hash_table_lookup(f->lid2guid,
					GINT_TO_POINTER(lid));

	return port;
}