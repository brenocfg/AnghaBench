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
typedef  int /*<<< orphan*/  treespace_t ;
typedef  scalar_t__ treeref_t ;

/* Variables and functions */
 int /*<<< orphan*/  free_intree_node (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ intree_remove (int /*<<< orphan*/ ,scalar_t__,int,scalar_t__*) ; 

inline treeref_t intree_delete (treespace_t TS, treeref_t T, int x) {
  treeref_t R, N;
  R = intree_remove (TS, T, x, &N);
  if (N) {
    free_intree_node (TS, N);
  }
  return R;
}