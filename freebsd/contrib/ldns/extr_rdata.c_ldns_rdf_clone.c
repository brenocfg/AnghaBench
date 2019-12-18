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
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_rdf_data (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ldns_rdf_get_type (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * ldns_rdf_new_frm_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_rdf_size (int /*<<< orphan*/  const*) ; 

ldns_rdf *
ldns_rdf_clone(const ldns_rdf *rd)
{
	assert(rd != NULL);
	return (ldns_rdf_new_frm_data( ldns_rdf_get_type(rd),
		ldns_rdf_size(rd), ldns_rdf_data(rd)));
}