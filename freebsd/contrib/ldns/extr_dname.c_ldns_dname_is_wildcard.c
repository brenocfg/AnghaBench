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
typedef  int /*<<< orphan*/  ldns_rdf ;

/* Variables and functions */
 scalar_t__ ldns_dname_label_count (int /*<<< orphan*/  const*) ; 
 char* ldns_rdf_data (int /*<<< orphan*/  const*) ; 

int
ldns_dname_is_wildcard(const ldns_rdf* dname)
{
	return ( ldns_dname_label_count(dname) > 0 &&
		 ldns_rdf_data(dname)[0] == 1 &&
		 ldns_rdf_data(dname)[1] == '*');
}