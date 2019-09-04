#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int x1; int x2; int y; scalar_t__ right; scalar_t__ left; } ;
typedef  TYPE_1__ rev_friends_t ;

/* Variables and functions */
 int /*<<< orphan*/  alloc_rev_friends_nodes ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 TYPE_1__* zmalloc (int) ; 

__attribute__((used)) static rev_friends_t *new_rev_friends_node (int x1, int x2, int y) {
  rev_friends_t *P;
  P = zmalloc (sizeof (rev_friends_t));
  assert (P);
  alloc_rev_friends_nodes++;
  P->left = P->right = 0;
  P->x1 = x1;
  P->x2 = x2;
  P->y = y;
  return P;
}