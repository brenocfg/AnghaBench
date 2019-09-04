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
struct ipv6 {scalar_t__* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

void set_bit (struct ipv6 *a, int level) {
  assert (level < 128);
  int q = (7 - (level / 16));
  a->data[q] += (1 << (level & 15));
  if (!a->data[q]) {
    q --;
    while (q >= 0) {
      a->data[q] ++;
      if (a->data[q]) {
        return;
      }
      q --;
    }
  }
}