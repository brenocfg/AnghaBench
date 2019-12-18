#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int delta; } ;
typedef  TYPE_1__ tree_ext_small_t ;
struct TYPE_6__ {int N; TYPE_1__** root; } ;
typedef  TYPE_2__ listree_t ;

/* Variables and functions */
 int /*<<< orphan*/  listree_get_kth (TYPE_2__*,int) ; 

__attribute__((used)) static inline void listree_get_kth_last (listree_t *LT, int k) {
  tree_ext_small_t *T = *LT->root;
  listree_get_kth (LT, LT->N + T->delta - 1 - k);
}