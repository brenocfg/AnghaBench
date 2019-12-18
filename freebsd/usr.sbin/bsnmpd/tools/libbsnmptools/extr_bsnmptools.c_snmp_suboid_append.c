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
struct asn_oid {scalar_t__ len; int /*<<< orphan*/ * subs; } ;
typedef  int int32_t ;
typedef  int /*<<< orphan*/  asn_subid_t ;

/* Variables and functions */
 scalar_t__ ASN_MAXOIDLEN ; 
 int /*<<< orphan*/  warnx (char*,scalar_t__) ; 

int32_t
snmp_suboid_append(struct asn_oid *var, asn_subid_t suboid)
{
	if (var == NULL)
		return (-1);

	if (var->len >= ASN_MAXOIDLEN) {
		warnx("Oid too long - %u", var->len);
		return (-1);
	}

	var->subs[var->len++] = suboid;

	return (1);
}