#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct node {int /*<<< orphan*/  n_key; TYPE_1__* n_parent; } ;
struct TYPE_2__ {int /*<<< orphan*/ * n_parent; } ;

/* Variables and functions */
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static bool
node_is_direct_key(const struct node *n)
{

	if (n->n_parent != NULL && n->n_parent->n_parent == NULL &&
	    strcmp(n->n_key, "/-") == 0) {
		return (true);
	}

	return (false);
}