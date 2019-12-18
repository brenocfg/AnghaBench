#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  x; } ;
typedef  TYPE_1__ tree_ext_large_t ;
struct tree_payload {int flags; int /*<<< orphan*/  global_id; } ;

/* Variables and functions */
 struct tree_payload* PAYLOAD (TYPE_1__*) ; 
 int /*<<< orphan*/  change_entry_flags_common (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static inline void change_entry_flags_memory (tree_ext_large_t *T, int new_flags) {
  struct tree_payload *P = PAYLOAD (T);
  change_entry_flags_common (T->x, P->global_id, P->flags, new_flags);
  P->flags = new_flags;
}