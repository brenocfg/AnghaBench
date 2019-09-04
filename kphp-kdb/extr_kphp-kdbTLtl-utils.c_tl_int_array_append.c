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
struct tl_int_array {scalar_t__ pos; scalar_t__ size; int* buff; } ;

/* Variables and functions */

int tl_int_array_append (struct tl_int_array *a, int i) {
  if (a->pos >= a->size) {
    return -1;
  }
  a->buff[(a->pos)++] = i;
  return 0;
}