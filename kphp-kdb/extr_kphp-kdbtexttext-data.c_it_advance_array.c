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
struct iterator {size_t array_cnt; int /*<<< orphan*/  tree_x; int /*<<< orphan*/  x; scalar_t__ array_x; scalar_t__* array_ptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  it_relax_x (struct iterator*) ; 

__attribute__((used)) static inline void it_advance_array (struct iterator *cur) {
  if (cur->array_cnt) {
    cur->array_x = cur->array_ptr[--cur->array_cnt];
    it_relax_x (cur);
  } else {
    cur->array_x = 0;
    cur->x = cur->tree_x;
  }
}