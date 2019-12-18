#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_2__* next_time; TYPE_1__* prev_time; } ;
typedef  TYPE_3__ wkey ;
struct TYPE_6__ {TYPE_1__* prev_time; } ;
struct TYPE_5__ {TYPE_2__* next_time; } ;

/* Variables and functions */

inline void del_entry_time (wkey *entry) {
  entry->next_time->prev_time = entry->prev_time;
  entry->prev_time->next_time = entry->next_time;
}