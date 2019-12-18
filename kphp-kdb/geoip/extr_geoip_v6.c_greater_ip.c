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

int greater_ip (struct ipv6 a, struct ipv6 b) {
  int i;
  for (i = 0; i < 8; i++) {
    if (a.data[i] > b.data[i]) { 
      return 1;
    }
    if (a.data[i] < b.data[i]) {
      return 0;
    }
  }
  return 0;
}