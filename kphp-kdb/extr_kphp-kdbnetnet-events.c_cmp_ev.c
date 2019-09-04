#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int priority; long long timestamp; } ;
typedef  TYPE_1__ event_t ;

/* Variables and functions */

int cmp_ev (event_t *ev1, event_t *ev2) {
  int x = ev1->priority - ev2->priority;
  long long t;
  if (x) return x;
  t = ev1->timestamp - ev2->timestamp;
  return t < 0 ? -1 : (t ? 1 : 0);
}