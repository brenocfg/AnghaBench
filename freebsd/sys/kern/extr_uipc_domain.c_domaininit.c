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

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  callout_init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  dom_mtx ; 
 int domain_init_status ; 
 int max_linkhdr ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pffast_callout ; 
 int /*<<< orphan*/  pfslow_callout ; 

__attribute__((used)) static void
domaininit(void *dummy)
{

	if (max_linkhdr < 16)		/* XXX */
		max_linkhdr = 16;

	callout_init(&pffast_callout, 1);
	callout_init(&pfslow_callout, 1);

	mtx_lock(&dom_mtx);
	KASSERT(domain_init_status == 0, ("domaininit called too late!"));
	domain_init_status = 1;
	mtx_unlock(&dom_mtx);
}