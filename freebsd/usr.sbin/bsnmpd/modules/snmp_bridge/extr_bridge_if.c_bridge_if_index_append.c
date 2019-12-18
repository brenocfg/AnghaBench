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
struct bridge_if {size_t* bif_name; } ;
struct asn_oid {size_t len; size_t* subs; } ;

/* Variables and functions */
 size_t strlen (size_t*) ; 

__attribute__((used)) static void
bridge_if_index_append(struct asn_oid *oid, uint sub,
	const struct bridge_if *bif)
{
	uint i;

	oid->len = sub + strlen(bif->bif_name) + 1;
	oid->subs[sub] = strlen(bif->bif_name);

	for (i = 1; i <= strlen(bif->bif_name); i++)
		oid->subs[sub + i] = bif->bif_name[i - 1];
}