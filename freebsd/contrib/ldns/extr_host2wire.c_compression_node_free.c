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
typedef  int /*<<< orphan*/  ldns_rdf ;
struct TYPE_4__ {scalar_t__ key; } ;
typedef  TYPE_1__ ldns_rbnode_t ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_FREE (TYPE_1__*) ; 
 int /*<<< orphan*/  ldns_rdf_deep_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
compression_node_free(ldns_rbnode_t *node, void *arg)
{
	(void)arg; /* Yes, dear compiler, it is used */
	ldns_rdf_deep_free((ldns_rdf *)node->key);
	LDNS_FREE(node);
}