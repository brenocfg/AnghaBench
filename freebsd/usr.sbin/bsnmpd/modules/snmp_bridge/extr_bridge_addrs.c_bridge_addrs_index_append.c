#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  size_t uint ;
struct tp_entry {size_t* tp_addr; } ;
struct asn_oid {size_t len; size_t* subs; } ;

/* Variables and functions */
 size_t ETHER_ADDR_LEN ; 

__attribute__((used)) static void
bridge_addrs_index_append(struct asn_oid *oid, uint sub,
	const struct tp_entry *te)
{
	int i;

	oid->len = sub + ETHER_ADDR_LEN + 1;
	oid->subs[sub] = ETHER_ADDR_LEN;

	for (i = 1; i <= ETHER_ADDR_LEN; i++)
		oid->subs[sub + i] = te->tp_addr[i - 1];
}