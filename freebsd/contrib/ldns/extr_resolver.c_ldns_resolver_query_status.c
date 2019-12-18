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
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  ldns_status ;
typedef  int /*<<< orphan*/  ldns_rr_type ;
typedef  int /*<<< orphan*/  ldns_rr_class ;
typedef  int /*<<< orphan*/  ldns_resolver ;
typedef  int /*<<< orphan*/  const ldns_rdf ;
typedef  int /*<<< orphan*/  ldns_pkt ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_STATUS_MEM_ERR ; 
 int /*<<< orphan*/  const* ldns_dname_cat_clone (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_rdf_free (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ldns_resolver_defnames (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_resolver_domain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_resolver_send (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

ldns_status
ldns_resolver_query_status(ldns_pkt** pkt,
		ldns_resolver *r, const ldns_rdf *name,
		ldns_rr_type t, ldns_rr_class c, uint16_t flags)
{
	ldns_rdf *newname;
	ldns_status status;

	if (!ldns_resolver_defnames(r) || !ldns_resolver_domain(r)) {
		return ldns_resolver_send(pkt, r, name, t, c, flags);
	}

	newname = ldns_dname_cat_clone(name, ldns_resolver_domain(r));
	if (!newname) {
		return LDNS_STATUS_MEM_ERR;
	}
	status = ldns_resolver_send(pkt, r, newname, t, c, flags);
	ldns_rdf_free(newname);
	return status;
}