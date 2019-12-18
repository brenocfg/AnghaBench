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
 int ldns_dname_compare (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int
ldns_dname_compare_v(const void *a, const void *b) {
	return ldns_dname_compare((ldns_rdf *)a, (ldns_rdf *)b);
}