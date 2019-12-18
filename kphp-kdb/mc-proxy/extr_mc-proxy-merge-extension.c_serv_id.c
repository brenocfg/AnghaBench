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
struct connection {scalar_t__ target; } ;
struct TYPE_2__ {int tot_buckets; scalar_t__* buckets; } ;

/* Variables and functions */
 TYPE_1__* CC ; 

int serv_id (struct connection *c) { 
  int i;
  for (i = 0; i < CC->tot_buckets; i++) {
    if (CC->buckets[i] == c->target) {
      return i;
    }
  }
  return -1;
}