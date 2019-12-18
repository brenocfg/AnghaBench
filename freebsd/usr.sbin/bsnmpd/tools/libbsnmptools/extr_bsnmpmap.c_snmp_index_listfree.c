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
struct snmp_idxlist {int dummy; } ;
struct index {scalar_t__ tc; int /*<<< orphan*/  snmp_enum; } ;

/* Variables and functions */
 scalar_t__ SNMP_TC_OWN ; 
 struct index* STAILQ_FIRST (struct snmp_idxlist*) ; 
 int /*<<< orphan*/  STAILQ_INIT (struct snmp_idxlist*) ; 
 int /*<<< orphan*/  STAILQ_REMOVE_HEAD (struct snmp_idxlist*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enum_pairs_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct index*) ; 
 int /*<<< orphan*/  link ; 

void
snmp_index_listfree(struct snmp_idxlist *headp)
{
	struct index *i;

	while ((i = STAILQ_FIRST(headp)) != NULL) {
		STAILQ_REMOVE_HEAD(headp, link);
		if (i->tc == SNMP_TC_OWN)
			enum_pairs_free(i->snmp_enum);
		free(i);
	}

	STAILQ_INIT(headp);
}