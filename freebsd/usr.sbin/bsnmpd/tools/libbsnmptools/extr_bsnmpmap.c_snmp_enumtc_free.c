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
struct enum_type {scalar_t__ snmp_enum; struct enum_type* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  enum_pairs_free (scalar_t__) ; 
 int /*<<< orphan*/  free (struct enum_type*) ; 

void
snmp_enumtc_free(struct enum_type *tc)
{
	if (tc->name)
		free(tc->name);
	if (tc->snmp_enum)
		enum_pairs_free(tc->snmp_enum);
	free(tc);
}