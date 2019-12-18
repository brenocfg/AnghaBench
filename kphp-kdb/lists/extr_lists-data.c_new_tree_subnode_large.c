#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int y; int rpos; int /*<<< orphan*/  x; int /*<<< orphan*/  right; int /*<<< orphan*/  left; } ;
typedef  TYPE_1__ tree_ext_large_t ;
struct tree_payload {int dummy; } ;
typedef  int /*<<< orphan*/  object_id_t ;

/* Variables and functions */
 int /*<<< orphan*/  NILL ; 
 int /*<<< orphan*/  PAYLOAD (TYPE_1__*) ; 
 int /*<<< orphan*/  alloc_large_nodes ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  object_id_bytes ; 
 int /*<<< orphan*/  tree_ext_large_node_size ; 
 TYPE_1__* zmalloc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline tree_ext_large_t *new_tree_subnode_large (object_id_t x, int y, int rpos) {
  tree_ext_large_t * P;
  P = zmalloc (tree_ext_large_node_size);
  assert (P);
  alloc_large_nodes++;
  P->left = P->right = NILL;
  P->y = y;
  P->rpos = rpos;
//  P->delta = rpos_to_delta[NODE_RPOS(p)];
  #ifdef LISTS_Z
  memcpy (P->x, x, object_id_bytes);
  #else
  P->x = x;
  #endif
  memset (PAYLOAD (P), 0, sizeof (struct tree_payload));
  return P;
}