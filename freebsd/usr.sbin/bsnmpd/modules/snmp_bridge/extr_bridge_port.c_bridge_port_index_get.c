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
struct bridge_port {scalar_t__ status; } ;
struct bridge_if {int dummy; } ;
struct asn_oid {size_t len; int* subs; } ;
typedef  scalar_t__ int8_t ;
typedef  char int32_t ;

/* Variables and functions */
 int IFNAMSIZ ; 
 scalar_t__ RowStatus_active ; 
 struct bridge_if* bridge_if_find_ifname (char*) ; 
 struct bridge_port* bridge_port_find (char,struct bridge_if*) ; 

__attribute__((used)) static struct bridge_port *
bridge_port_index_get(const struct asn_oid *oid, uint sub, int8_t status)
{
	uint i;
	int32_t port_no;
	char bif_name[IFNAMSIZ];
	struct bridge_if *bif;
	struct bridge_port *bp;

	if (oid->len - sub != oid->subs[sub] + 2 ||
	    oid->subs[sub] >= IFNAMSIZ)
		return (NULL);

	for (i = 0; i < oid->subs[sub]; i++)
		bif_name[i] = oid->subs[sub + i + 1];
	bif_name[i] = '\0';

	port_no = oid->subs[sub + i + 1];

	if ((bif = bridge_if_find_ifname(bif_name)) == NULL)
		return (NULL);

	if ((bp = bridge_port_find(port_no, bif)) == NULL ||
	    (status == 0 && bp->status != RowStatus_active))
		return (NULL);

	return (bp);
}