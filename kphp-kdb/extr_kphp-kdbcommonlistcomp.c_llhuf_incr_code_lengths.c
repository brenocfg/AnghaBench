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
struct ccp_list_entry {size_t leaf_value; struct ccp_list_entry* right; struct ccp_list_entry* left; } ;

/* Variables and functions */

__attribute__((used)) static void llhuf_incr_code_lengths (int *l, struct ccp_list_entry *x) {
  if (x->leaf_value >= 0) {
    l[x->leaf_value]++;
  } else {
    llhuf_incr_code_lengths (l, x->left);
    llhuf_incr_code_lengths (l, x->right);
  }
}