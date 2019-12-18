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
typedef  int /*<<< orphan*/  ldns_resolver ;
typedef  int /*<<< orphan*/  ldns_rdf ;
typedef  int /*<<< orphan*/  ldns_pkt ;

/* Variables and functions */
 int /*<<< orphan*/ * ldns_resolver_domain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ ** ldns_resolver_searchlist (int /*<<< orphan*/ *) ; 
 int ldns_resolver_searchlist_count (int /*<<< orphan*/ *) ; 
 scalar_t__ query (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int) ; 
 int /*<<< orphan*/ * safe_dname_cat_clone (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static ldns_rdf *
search(ldns_resolver *res, ldns_rdf *domain, ldns_pkt **pkt,
    bool absolute, bool close_tcp) {
    ldns_rdf *dname, **searchlist;
    int i, n;

    if (absolute && query(res, domain, pkt, close_tcp))
        return domain;

    if ((dname = ldns_resolver_domain(res)) != NULL) {
        dname = safe_dname_cat_clone(domain, dname);
        if (query(res, dname, pkt, close_tcp))
            return dname;
    }

    searchlist = ldns_resolver_searchlist(res);
    n = ldns_resolver_searchlist_count(res);
    for (i = 0; i < n; i++) {
        dname = safe_dname_cat_clone(domain, searchlist[i]);
        if (query(res, dname, pkt, close_tcp))
            return dname;
    }

    if (!absolute && query(res, domain, pkt, close_tcp))
        return domain;

    return NULL;
}