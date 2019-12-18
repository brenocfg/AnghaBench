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
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dom_mtx ; 
 int domain_init_status ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pffast_callout ; 
 int /*<<< orphan*/  pffasttimo ; 
 int /*<<< orphan*/  pfslow_callout ; 
 int /*<<< orphan*/  pfslowtimo ; 

__attribute__((used)) static void
domainfinalize(void *dummy)
{

	mtx_lock(&dom_mtx);
	KASSERT(domain_init_status == 1, ("domainfinalize called too late!"));
	domain_init_status = 2;
	mtx_unlock(&dom_mtx);	

	callout_reset(&pffast_callout, 1, pffasttimo, NULL);
	callout_reset(&pfslow_callout, 1, pfslowtimo, NULL);
}