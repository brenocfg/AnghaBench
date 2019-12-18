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
typedef  scalar_t__ uint ;
struct bridge_if {int dummy; } ;
struct asn_oid {scalar_t__ len; int* subs; } ;

/* Variables and functions */
 int IFNAMSIZ ; 
 struct bridge_if* bridge_first_bif () ; 
 struct bridge_if* bridge_if_find_ifname (char*) ; 
 struct bridge_if* bridge_next_bif (struct bridge_if*) ; 

__attribute__((used)) static struct bridge_if *
bridge_if_index_getnext(const struct asn_oid *oid, uint sub)
{
	uint i;
	char bif_name[IFNAMSIZ];
	struct bridge_if *bif;

	if (oid->len - sub == 0)
		return (bridge_first_bif());

	if (oid->len - sub != oid->subs[sub] + 1 || oid->subs[sub] >= IFNAMSIZ)
		return (NULL);

	for (i = 0; i < oid->subs[sub]; i++)
		bif_name[i] = oid->subs[sub + i + 1];
	bif_name[i] = '\0';

	if ((bif = bridge_if_find_ifname(bif_name)) == NULL)
		return (NULL);

	return (bridge_next_bif(bif));
}