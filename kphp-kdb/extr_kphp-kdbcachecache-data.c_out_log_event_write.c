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
struct TYPE_2__ {int sz; int /*<<< orphan*/  b; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 TYPE_1__ le_buff ; 
 int /*<<< orphan*/  writeout (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void out_log_event_write (long long *events) {
  assert (le_buff.sz);
  assert (!(le_buff.sz & 3));
  writeout (le_buff.b, le_buff.sz);
  le_buff.sz = 0;
  (*events)++;
}