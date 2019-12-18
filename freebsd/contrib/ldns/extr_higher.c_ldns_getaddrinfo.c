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
typedef  scalar_t__ uint16_t ;
typedef  scalar_t__ ldns_status ;
typedef  int /*<<< orphan*/  ldns_rr_list ;
typedef  int /*<<< orphan*/  ldns_rr_class ;
typedef  int /*<<< orphan*/  ldns_resolver ;
typedef  scalar_t__ ldns_rdf_type ;
typedef  int /*<<< orphan*/  ldns_rdf ;

/* Variables and functions */
 scalar_t__ LDNS_RDF_TYPE_A ; 
 scalar_t__ LDNS_RDF_TYPE_AAAA ; 
 scalar_t__ LDNS_RDF_TYPE_DNAME ; 
 scalar_t__ LDNS_STATUS_OK ; 
 int /*<<< orphan*/ * ldns_get_rr_list_addr_by_name (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ldns_get_rr_list_name_by_addr (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ldns_rdf_get_type (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ldns_resolver_deep_free (int /*<<< orphan*/ *) ; 
 scalar_t__ ldns_resolver_new_frm_file (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 scalar_t__ ldns_rr_list_rr_count (int /*<<< orphan*/ *) ; 

uint16_t
ldns_getaddrinfo(ldns_resolver *res, const ldns_rdf *node,
		ldns_rr_class c, ldns_rr_list **ret)
{
	ldns_rdf_type t;
	uint16_t names_found;
	ldns_resolver *r;
	ldns_status s;

	t = ldns_rdf_get_type(node);
	names_found = 0;
	r = res;

	if (res == NULL) {
		/* prepare a new resolver, using /etc/resolv.conf as a guide  */
		s = ldns_resolver_new_frm_file(&r, NULL);
		if (s != LDNS_STATUS_OK) {
			return 0;
		} 
	}

	if (t == LDNS_RDF_TYPE_DNAME) {
		/* we're asked to query for a name */
		*ret = ldns_get_rr_list_addr_by_name(r, node, c, 0);
		names_found = ldns_rr_list_rr_count(*ret);
	}

	if (t == LDNS_RDF_TYPE_A || t == LDNS_RDF_TYPE_AAAA) {
		/* an address */
		*ret = ldns_get_rr_list_name_by_addr(r, node, c, 0);
		names_found = ldns_rr_list_rr_count(*ret);
	}

	if (res == NULL) {
		ldns_resolver_deep_free(r);
	}
	
	return names_found;
}