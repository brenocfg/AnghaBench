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
struct snmp_enum_tc {int dummy; } ;
struct enum_type {int /*<<< orphan*/  snmp_enum; struct enum_type* name; } ;

/* Variables and functions */
 struct enum_type* SLIST_FIRST (struct snmp_enum_tc*) ; 
 int /*<<< orphan*/  SLIST_REMOVE_HEAD (struct snmp_enum_tc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enum_pairs_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct enum_type*) ; 
 int /*<<< orphan*/  link ; 

__attribute__((used)) static void
snmp_enumtc_listfree(struct snmp_enum_tc *headp)
{
	struct enum_type *t;

	while ((t = SLIST_FIRST(headp)) != NULL) {
		SLIST_REMOVE_HEAD(headp, link);

		if (t->name)
			free(t->name);
		enum_pairs_free(t->snmp_enum);
		free(t);
	}
}