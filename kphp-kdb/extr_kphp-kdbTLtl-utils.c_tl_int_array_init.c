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
struct tl_int_array {int* buff; int size; scalar_t__ pos; } ;

/* Variables and functions */

void tl_int_array_init (struct tl_int_array *a, int *buff, int size) {
  a->buff = buff;
  a->size = size;
  a->pos = 0;
}