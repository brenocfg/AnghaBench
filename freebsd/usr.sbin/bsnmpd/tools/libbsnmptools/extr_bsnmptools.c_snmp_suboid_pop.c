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
struct asn_oid {int len; int* subs; } ;
typedef  int int32_t ;
typedef  int asn_subid_t ;

/* Variables and functions */

int32_t
snmp_suboid_pop(struct asn_oid *var)
{
	asn_subid_t suboid;

	if (var == NULL)
		return (-1);

	if (var->len < 1)
		return (-1);

	suboid = var->subs[--(var->len)];
	var->subs[var->len] = 0;

	return (suboid);
}