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
typedef  scalar_t__ ldns_status ;
typedef  int /*<<< orphan*/  ldns_resolver ;

/* Variables and functions */
 scalar_t__ LDNS_STATUS_MEM_ERR ; 
 scalar_t__ LDNS_STATUS_OK ; 
 int /*<<< orphan*/ * ldns_resolver_new () ; 
 scalar_t__ ldns_resolver_new_frm_file (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 

__attribute__((used)) static ldns_status
ldns_resolver_new_default(ldns_resolver **res) {
    if (ldns_resolver_new_frm_file(res, NULL) == LDNS_STATUS_OK ||
        (*res = ldns_resolver_new()) != NULL)
        return LDNS_STATUS_OK;
    return LDNS_STATUS_MEM_ERR;
}