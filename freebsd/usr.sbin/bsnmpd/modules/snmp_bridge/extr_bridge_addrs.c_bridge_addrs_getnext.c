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
typedef  int uint8_t ;
typedef  size_t uint ;
struct tp_entry {int dummy; } ;
struct bridge_if {int dummy; } ;
struct asn_oid {scalar_t__ len; int* subs; } ;

/* Variables and functions */
 int ETHER_ADDR_LEN ; 
 struct tp_entry* bridge_addrs_bif_first (struct bridge_if*) ; 
 struct tp_entry* bridge_addrs_bif_next (struct tp_entry*) ; 
 struct tp_entry* bridge_addrs_find (int*,struct bridge_if*) ; 

__attribute__((used)) static struct tp_entry *
bridge_addrs_getnext(const struct asn_oid *oid, uint sub,
	struct bridge_if *bif)
{
	int i;
	uint8_t tp_addr[ETHER_ADDR_LEN];
	static struct tp_entry *te;

	if (oid->len - sub == 0)
		return (bridge_addrs_bif_first(bif));

	if (oid->len - sub != ETHER_ADDR_LEN + 1 ||
	    oid->subs[sub] != ETHER_ADDR_LEN)
		return (NULL);

	for (i = 0; i < ETHER_ADDR_LEN; i++)
		tp_addr[i] = oid->subs[sub + i + 1];

	if ((te = bridge_addrs_find(tp_addr, bif)) == NULL)
		return (NULL);

	return (bridge_addrs_bif_next(te));
}