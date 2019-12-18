#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_2__* head; int /*<<< orphan*/  num_active_node; int /*<<< orphan*/  mctx; } ;
typedef  TYPE_1__ isc_radix_tree_t ;
struct TYPE_7__ {struct TYPE_7__* l; struct TYPE_7__* r; int /*<<< orphan*/ * prefix; struct TYPE_7__* parent; int /*<<< orphan*/ ** data; } ;
typedef  TYPE_2__ isc_radix_node_t ;

/* Variables and functions */
 int /*<<< orphan*/  INSIST (int) ; 
 int /*<<< orphan*/  REQUIRE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _deref_prefix (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  isc_mem_put (int /*<<< orphan*/ ,TYPE_2__*,int) ; 

void
isc_radix_remove(isc_radix_tree_t *radix, isc_radix_node_t *node) {
	isc_radix_node_t *parent, *child;

	REQUIRE(radix != NULL);
	REQUIRE(node != NULL);

	if (node->r && node->l) {
		/*
		 * This might be a placeholder node -- have to check and
		 * make sure there is a prefix associated with it!
		 */
		if (node->prefix != NULL)
			_deref_prefix(radix->mctx, node->prefix);

		node->prefix = NULL;
		node->data[0] = node->data[1] = NULL;
		return;
	}

	if (node->r == NULL && node->l == NULL) {
		parent = node->parent;
		_deref_prefix(radix->mctx, node->prefix);
		isc_mem_put(radix->mctx, node, sizeof(*node));
		radix->num_active_node--;

		if (parent == NULL) {
			INSIST(radix->head == node);
			radix->head = NULL;
			return;
		}

		if (parent->r == node) {
			parent->r = NULL;
			child = parent->l;
		} else {
			INSIST(parent->l == node);
			parent->l = NULL;
			child = parent->r;
		}

		if (parent->prefix)
			return;

		/* We need to remove parent too. */

		if (parent->parent == NULL) {
			INSIST(radix->head == parent);
			radix->head = child;
		} else if (parent->parent->r == parent) {
			parent->parent->r = child;
		} else {
			INSIST(parent->parent->l == parent);
			parent->parent->l = child;
		}
		child->parent = parent->parent;
		isc_mem_put(radix->mctx, parent, sizeof(*parent));
		radix->num_active_node--;
		return;
	}

	if (node->r) {
		child = node->r;
	} else {
		INSIST(node->l != NULL);
		child = node->l;
	}
	parent = node->parent;
	child->parent = parent;

	_deref_prefix(radix->mctx, node->prefix);
	isc_mem_put(radix->mctx, node, sizeof(*node));
	radix->num_active_node--;

	if (parent == NULL) {
		INSIST(radix->head == node);
		radix->head = child;
		return;
	}

	if (parent->r == node) {
		parent->r = child;
	} else {
		INSIST(parent->l == node);
		parent->l = child;
	}
}