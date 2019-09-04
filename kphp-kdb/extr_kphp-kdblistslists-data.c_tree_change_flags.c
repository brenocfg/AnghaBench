#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tree_ext_small_t ;
typedef  int /*<<< orphan*/  tree_ext_large_t ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/ * LARGE_NODE (int /*<<< orphan*/ *) ; 
 TYPE_1__* PAYLOAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  change_entry_flags_memory (int /*<<< orphan*/ *,int) ; 
 int f_and_c ; 
 int f_and_s ; 
 int /*<<< orphan*/  f_cnt ; 
 int f_xor_c ; 
 int f_xor_s ; 

__attribute__((used)) static int tree_change_flags (tree_ext_small_t *TS) {
  tree_ext_large_t *T = LARGE_NODE(TS);
  if (!((PAYLOAD (T)->flags ^ f_xor_c) & f_and_c)) {
    change_entry_flags_memory (T, (PAYLOAD (T)->flags & f_and_s) ^ f_xor_s);
    f_cnt++;
  }
  return 0;
}