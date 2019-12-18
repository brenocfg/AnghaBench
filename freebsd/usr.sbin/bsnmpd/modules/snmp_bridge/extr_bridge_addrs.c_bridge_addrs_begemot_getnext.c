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
typedef  char uint8_t ;
typedef  scalar_t__ uint ;
struct tp_entry {int dummy; } ;
struct bridge_if {int dummy; } ;
struct asn_oid {scalar_t__ len; scalar_t__* subs; } ;

/* Variables and functions */
 int ETHER_ADDR_LEN ; 
 int IFNAMSIZ ; 
 struct tp_entry* bridge_addrs_find (char*,struct bridge_if*) ; 
 struct tp_entry* bridge_addrs_first () ; 
 struct tp_entry* bridge_addrs_next (struct tp_entry*) ; 
 struct bridge_if* bridge_if_find_ifname (char*) ; 

__attribute__((used)) static struct tp_entry *
bridge_addrs_begemot_getnext(const struct asn_oid *oid, uint sub)
{
	uint i, n_len;
	uint8_t tp_addr[ETHER_ADDR_LEN];
	char bif_name[IFNAMSIZ];
	struct bridge_if *bif;
	struct tp_entry *tp;

	if (oid->len - sub == 0)
		return (bridge_addrs_first());

	n_len = oid->subs[sub];
	if (oid->len - sub != n_len + ETHER_ADDR_LEN + 2 ||
	    n_len >= IFNAMSIZ || oid->subs[sub + n_len + 1] != ETHER_ADDR_LEN)
		return (NULL);

	for (i = 1; i <= n_len; i++)
		bif_name[i - 1] = oid->subs[sub + i];

	bif_name[i - 1] = '\0';

	for (i = 1; i <= ETHER_ADDR_LEN; i++)
		tp_addr[i - 1] = oid->subs[sub + n_len + i + 1];

	if ((bif = bridge_if_find_ifname(bif_name)) == NULL ||
	    (tp = bridge_addrs_find(tp_addr, bif)) == NULL)
		return (NULL);

	return (bridge_addrs_next(tp));
}