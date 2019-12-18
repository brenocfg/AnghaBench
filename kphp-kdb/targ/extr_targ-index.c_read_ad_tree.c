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
typedef  int /*<<< orphan*/  treeref_t ;

/* Variables and functions */
 int /*<<< orphan*/  AdSpace ; 
 int /*<<< orphan*/  assert (int) ; 
 int idx_load_next (int) ; 
 int idx_rptr ; 
 int /*<<< orphan*/  intree_build_from_list (int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  targeting_disabled ; 

treeref_t read_ad_tree (int nodes) {
  assert (nodes >= 0);
  if (!nodes) {
    return 0;
  }
  assert (idx_load_next (nodes * 8) >= nodes * 8);
  int *A = (int *) idx_rptr;
  idx_rptr += nodes * 8;
  if (!targeting_disabled) {
    return intree_build_from_list (AdSpace, A, nodes);
  }
  return 0;
}