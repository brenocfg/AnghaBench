#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ data; } ;
typedef  TYPE_1__ ldns_rbnode_t ;
typedef  int /*<<< orphan*/  ldns_dnssec_name ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_FREE (TYPE_1__*) ; 
 int /*<<< orphan*/  ldns_dnssec_name_deep_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ldns_dnssec_name_node_deep_free(ldns_rbnode_t *node, void *arg) {
	(void) arg;
	ldns_dnssec_name_deep_free((ldns_dnssec_name *)node->data);
	LDNS_FREE(node);
}