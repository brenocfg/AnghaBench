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
struct TYPE_5__ {int y; int rpos; int /*<<< orphan*/  z; int /*<<< orphan*/  x; int /*<<< orphan*/  right; int /*<<< orphan*/  left; } ;
typedef  TYPE_1__ tree_ext_global_t ;
typedef  int /*<<< orphan*/  object_id_t ;
typedef  int /*<<< orphan*/  global_id_t ;

/* Variables and functions */
 int /*<<< orphan*/  NILG ; 
 int /*<<< orphan*/  alloc_global_nodes ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  object_id_bytes ; 
 int /*<<< orphan*/  tree_ext_global_node_size ; 
 TYPE_1__* zmalloc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline tree_ext_global_t *new_tree_subnode_global (global_id_t x, int y, int rpos, object_id_t z) {
  tree_ext_global_t *P;
  P = zmalloc (tree_ext_global_node_size);
  assert (P);
  alloc_global_nodes++;
  P->left = P->right = NILG;
  P->y = y;
  P->rpos = rpos;
  P->x = x;

  #ifdef LISTS_Z
  memcpy (P->z, z, object_id_bytes);
  #else
  P->z = z;
  #endif
//  P->delta = rpos_to_delta[NODE_RPOS(p)];
  return P;
}