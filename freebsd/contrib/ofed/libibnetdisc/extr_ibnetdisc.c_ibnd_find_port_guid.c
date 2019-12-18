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
typedef  scalar_t__ uint64_t ;
struct TYPE_5__ {scalar_t__ guid; struct TYPE_5__* htnext; } ;
typedef  TYPE_1__ ibnd_port_t ;
struct TYPE_6__ {TYPE_1__** portstbl; } ;
typedef  TYPE_2__ ibnd_fabric_t ;

/* Variables and functions */
 int HASHGUID (scalar_t__) ; 
 int HTSZ ; 
 int /*<<< orphan*/  IBND_DEBUG (char*) ; 

ibnd_port_t *ibnd_find_port_guid(ibnd_fabric_t * fabric, uint64_t guid)
{
	int hash = HASHGUID(guid) % HTSZ;
	ibnd_port_t *port;

	if (!fabric) {
		IBND_DEBUG("fabric parameter NULL\n");
		return NULL;
	}

	for (port = fabric->portstbl[hash]; port; port = port->htnext)
		if (port->guid == guid)
			return port;

	return NULL;
}