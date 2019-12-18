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
struct lockf_entry {int /*<<< orphan*/  lf_outedges; } ;
struct lockf_edge {int dummy; } ;

/* Variables and functions */
 struct lockf_edge* LIST_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lf_remove_edge (struct lockf_edge*) ; 

__attribute__((used)) static void
lf_remove_outgoing(struct lockf_entry *x)
{
	struct lockf_edge *e;

	while ((e = LIST_FIRST(&x->lf_outedges)) != NULL) {
		lf_remove_edge(e);
	}
}