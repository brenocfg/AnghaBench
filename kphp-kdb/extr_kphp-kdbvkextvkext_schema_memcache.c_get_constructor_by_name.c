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
struct tl_type {int constructors_num; TYPE_1__** constructors; } ;
struct TYPE_2__ {int name; } ;

/* Variables and functions */

int get_constructor_by_name (struct tl_type *t, int name) {
  int i;
  for (i = 0; i < t->constructors_num; i++) if (t->constructors[i]->name == name) {
    return i;
  }
  return -1;
}