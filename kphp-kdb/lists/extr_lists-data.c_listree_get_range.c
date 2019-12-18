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
struct TYPE_6__ {int delta; } ;
typedef  TYPE_1__ tree_ext_small_t ;
struct TYPE_7__ {int N; TYPE_1__** root; } ;
typedef  TYPE_2__ listree_t ;

/* Variables and functions */
 scalar_t__ listree_get_range_rec (TYPE_1__*,TYPE_2__*,int,int) ; 

__attribute__((used)) static int listree_get_range (listree_t *LT, int k, int n) {
  tree_ext_small_t *T = *LT->root;
  int G_N = LT->N;
  int M = G_N + T->delta;
  n += k;
  if (k < 0) { 
    k = 0; 
  }
  if (n > M) {
    n = M;
  }
  if (n <= k) {
    return 0;
  }
  if (listree_get_range_rec (T, LT, k, n - 1) < 0) {
    return -2;
  } else {
    return n - k;
  }
}