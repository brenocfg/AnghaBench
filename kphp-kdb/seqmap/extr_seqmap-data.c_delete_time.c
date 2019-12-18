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
struct item {TYPE_1__* prev_time; TYPE_1__* next_time; } ;
struct TYPE_2__ {struct TYPE_2__* next_time; struct TYPE_2__* prev_time; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 

void delete_time (struct item *I) {
  if (!I->next_time) { return; }
  assert (I->prev_time);
  I->next_time->prev_time = I->prev_time;
  I->prev_time->next_time = I->next_time;
  I->next_time = I->prev_time = 0;
}