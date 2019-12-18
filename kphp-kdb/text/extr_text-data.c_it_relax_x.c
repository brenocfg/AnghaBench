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
struct iterator {scalar_t__ array_x; scalar_t__ tree_x; scalar_t__ x; } ;

/* Variables and functions */

__attribute__((used)) static inline void it_relax_x (struct iterator *cur) {
  if (cur->array_x > cur->tree_x) {
    cur->x = cur->array_x;
  } else {
    cur->x = cur->tree_x;
  }
}