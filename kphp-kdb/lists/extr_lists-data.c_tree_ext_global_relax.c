#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_2__* right; TYPE_1__* left; scalar_t__ delta; } ;
typedef  TYPE_3__ tree_ext_global_t ;
struct TYPE_7__ {scalar_t__ delta; } ;
struct TYPE_6__ {scalar_t__ delta; } ;

/* Variables and functions */
 size_t NODE_TYPE (TYPE_3__*) ; 
 scalar_t__* rpos_to_delta ; 

__attribute__((used)) static inline void tree_ext_global_relax (tree_ext_global_t *T) {
  T->delta = T->left->delta + T->right->delta + rpos_to_delta[NODE_TYPE(T)];
}