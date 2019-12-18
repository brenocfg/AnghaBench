#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_2__* right; TYPE_1__* left; scalar_t__ N; } ;
typedef  TYPE_3__ tree_num_t ;
struct TYPE_6__ {scalar_t__ N; } ;
struct TYPE_5__ {scalar_t__ N; } ;

/* Variables and functions */

__attribute__((used)) static inline void tree_num_relax (tree_num_t *T) {
  T->N = T->left->N + T->right->N + 1;
}