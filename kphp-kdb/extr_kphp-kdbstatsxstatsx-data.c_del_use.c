#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct counter {TYPE_2__* prev_use; TYPE_1__* next_use; } ;
struct TYPE_4__ {TYPE_1__* next_use; } ;
struct TYPE_3__ {TYPE_2__* prev_use; } ;

/* Variables and functions */

__attribute__((used)) static void del_use (struct counter *C) {
  if (C->prev_use && C->next_use) {
    C->next_use->prev_use = C->prev_use;
    C->prev_use->next_use = C->next_use;
    C->next_use = 0;
    C->prev_use = 0;
  }
}