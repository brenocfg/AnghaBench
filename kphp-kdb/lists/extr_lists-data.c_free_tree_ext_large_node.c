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
typedef  int /*<<< orphan*/  tree_ext_large_t ;
struct tree_payload {scalar_t__ text; } ;

/* Variables and functions */
 scalar_t__ MDataEnd ; 
 int NODE_TYPE (int /*<<< orphan*/ *) ; 
 struct tree_payload* PAYLOAD (int /*<<< orphan*/ *) ; 
 int TF_PLUS ; 
 int TF_ZERO ; 
 int /*<<< orphan*/  alloc_large_nodes ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ empty_string ; 
 int /*<<< orphan*/  get_text_data_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tree_ext_large_node_size ; 
 int /*<<< orphan*/  zfree (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void free_tree_ext_large_node (tree_ext_large_t *T) {
  int tp = NODE_TYPE (T);
  struct tree_payload *P = PAYLOAD (T);
  if (tp == TF_ZERO || tp == TF_PLUS) {
    if (P->text && P->text != empty_string) {
      assert (P->text >= MDataEnd);
      zfree (P->text, get_text_data_len (P->text));
    }
    P->text = 0;
  } else {
    assert (!P->text);
  }
  alloc_large_nodes--;
  zfree (T, tree_ext_large_node_size);
}