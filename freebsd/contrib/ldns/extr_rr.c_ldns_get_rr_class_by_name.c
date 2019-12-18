#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ldns_rr_class ;
struct TYPE_3__ {int /*<<< orphan*/  id; } ;
typedef  TYPE_1__ ldns_lookup_table ;

/* Variables and functions */
 int /*<<< orphan*/  atoi (char const*) ; 
 TYPE_1__* ldns_lookup_by_name (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  ldns_rr_classes ; 
 int strlen (char const*) ; 
 scalar_t__ strncasecmp (char const*,char*,int) ; 

ldns_rr_class
ldns_get_rr_class_by_name(const char *name)
{
	ldns_lookup_table *lt;

	/* CLASSXX representation */
	if (strlen(name) > 5 && strncasecmp(name, "CLASS", 5) == 0) {
		return atoi(name + 5);
	}

	/* Normal types */
	lt = ldns_lookup_by_name(ldns_rr_classes, name);

	if (lt) {
		return lt->id;
	}
	return 0;
}