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
struct tl_int_array {int pos; int size; int /*<<< orphan*/ * buff; } ;

/* Variables and functions */

int tl_int_array_append_long (struct tl_int_array *a, long long l) {
  if (a->pos >= a->size - 1) {
    return -1;
  }
  *((long long *) (&a->buff[a->pos])) = l;
  a->pos += 2;
  return 0;
}