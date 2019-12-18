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
struct relative {int type; struct relative* next; int /*<<< orphan*/  timestamp; } ;
struct TYPE_2__ {struct relative* next; } ;

/* Variables and functions */
 TYPE_1__ RELATIVES ; 
 int /*<<< orphan*/  precise_now ; 

void restart_friends_timers (void) {
  struct relative *cur = RELATIVES.next;
  while (cur->type != -1) {
    cur->timestamp = precise_now;
    cur = cur->next;
  }
}