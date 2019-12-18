#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_1__* port; struct TYPE_9__* htnext; } ;
typedef  TYPE_2__ ibnd_port_cache_t ;
struct TYPE_10__ {scalar_t__ guid; scalar_t__ portnum; } ;
typedef  TYPE_3__ ibnd_port_cache_key_t ;
struct TYPE_11__ {TYPE_2__** portscachetbl; } ;
typedef  TYPE_4__ ibnd_fabric_cache_t ;
struct TYPE_8__ {scalar_t__ guid; scalar_t__ portnum; } ;

/* Variables and functions */
 int HASHGUID (scalar_t__) ; 
 int HTSZ ; 

__attribute__((used)) static ibnd_port_cache_t *_find_port(ibnd_fabric_cache_t * fabric_cache,
				     ibnd_port_cache_key_t * port_cache_key)
{
	int hash_indx = HASHGUID(port_cache_key->guid) % HTSZ;
	ibnd_port_cache_t *port_cache;

	for (port_cache = fabric_cache->portscachetbl[hash_indx];
	     port_cache; port_cache = port_cache->htnext) {
		if (port_cache->port->guid == port_cache_key->guid
		    && port_cache->port->portnum == port_cache_key->portnum)
			return port_cache;
	}

	return NULL;
}