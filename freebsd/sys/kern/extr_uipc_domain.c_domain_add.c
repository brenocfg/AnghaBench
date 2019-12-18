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
struct domain {char* dom_name; struct domain* dom_next; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  dom_mtx ; 
 int domain_init_status ; 
 struct domain* domains ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 

void
domain_add(void *data)
{
	struct domain *dp;

	dp = (struct domain *)data;
	mtx_lock(&dom_mtx);
	dp->dom_next = domains;
	domains = dp;

	KASSERT(domain_init_status >= 1,
	    ("attempt to domain_add(%s) before domaininit()",
	    dp->dom_name));
#ifndef INVARIANTS
	if (domain_init_status < 1)
		printf("WARNING: attempt to domain_add(%s) before "
		    "domaininit()\n", dp->dom_name);
#endif
#ifdef notyet
	KASSERT(domain_init_status < 2,
	    ("attempt to domain_add(%s) after domainfinalize()",
	    dp->dom_name));
#else
	if (domain_init_status >= 2)
		printf("WARNING: attempt to domain_add(%s) after "
		    "domainfinalize()\n", dp->dom_name);
#endif
	mtx_unlock(&dom_mtx);
}