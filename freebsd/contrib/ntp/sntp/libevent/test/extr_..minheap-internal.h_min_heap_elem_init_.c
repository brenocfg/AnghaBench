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
struct TYPE_2__ {int min_heap_idx; } ;
struct event {TYPE_1__ ev_timeout_pos; } ;

/* Variables and functions */

void min_heap_elem_init_(struct event* e) { e->ev_timeout_pos.min_heap_idx = -1; }