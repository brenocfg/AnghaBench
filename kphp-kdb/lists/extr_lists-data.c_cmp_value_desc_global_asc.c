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
typedef  scalar_t__ value_t ;
struct heap_entry {scalar_t__ value; int global_id; } ;
typedef  int global_id_t ;

/* Variables and functions */

int cmp_value_desc_global_asc (struct heap_entry *p, value_t value, global_id_t global_id) {
  if (p->value > value) {
    return -1;
  } else if (p->value < value) {
    return 1;
  } else {
    return p->global_id - global_id;
  }
}