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
struct tree {size_t nc; int /*<<< orphan*/ * c; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (size_t) ; 
 int /*<<< orphan*/  tree_delete (int /*<<< orphan*/ ) ; 

void tree_del_child (struct tree *P) {
  assert (P->nc);
  tree_delete (P->c[--P->nc]);
}