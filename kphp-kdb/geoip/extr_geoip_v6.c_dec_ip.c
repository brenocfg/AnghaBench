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
struct ipv6 {int* data; } ;

/* Variables and functions */

void dec_ip (struct ipv6 *a) {
  int i = 7;
  while (i >= 0) {
    if (a->data[i] > 0) {
      a->data[i] --;
      return;
    } else {
      a->data[i] = 0xffff;
      i --;
    }
  }
}