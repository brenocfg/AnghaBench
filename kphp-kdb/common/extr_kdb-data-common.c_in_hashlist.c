#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ hash_t ;
struct TYPE_3__ {int len; scalar_t__* A; } ;
typedef  TYPE_1__ hash_list_t ;

/* Variables and functions */

int in_hashlist (hash_t x, hash_list_t *L) {
  int a, b, c;
  if (!L) { return 0; }
  a = -1;  b = L->len;
  while (b - a > 1) {
    c = (a + b) >> 1;
    if (L->A[c] < x) {
      a = c;
    } else if (L->A[c] > x) {
      b = c;
    } else {
      return c + 1;
    }
  }
  return 0;
}