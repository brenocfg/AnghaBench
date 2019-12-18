#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ldns_rbtree_t ;
struct TYPE_9__ {scalar_t__ data; } ;
typedef  TYPE_1__ ldns_rbnode_t ;
struct TYPE_10__ {int flags; } ;
typedef  TYPE_2__ ldns_output_format ;
typedef  int /*<<< orphan*/  ldns_dnssec_name ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int LDNS_COMMENT_LAYOUT ; 
 TYPE_1__* LDNS_RBTREE_NULL ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ldns_dnssec_name_print_soa_fmt (int /*<<< orphan*/ *,TYPE_2__ const*,int /*<<< orphan*/ *,int) ; 
 TYPE_1__* ldns_rbtree_first (int /*<<< orphan*/  const*) ; 
 TYPE_1__* ldns_rbtree_next (TYPE_1__*) ; 

void
ldns_dnssec_zone_names_print_fmt(FILE *out, const ldns_output_format *fmt,
		const ldns_rbtree_t *tree, 
		bool print_soa)
{
	ldns_rbnode_t *node;
	ldns_dnssec_name *name;

	node = ldns_rbtree_first(tree);
	while (node != LDNS_RBTREE_NULL) {
		name = (ldns_dnssec_name *) node->data;
		ldns_dnssec_name_print_soa_fmt(out, fmt, name, print_soa);
		if ((fmt->flags & LDNS_COMMENT_LAYOUT))
			fprintf(out, ";\n");
		node = ldns_rbtree_next(node);
	}
}