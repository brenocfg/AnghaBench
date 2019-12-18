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
struct ub_event_base {int dummy; } ;
struct comm_base {TYPE_1__* eb; } ;
struct TYPE_2__ {struct ub_event_base* base; } ;

/* Variables and functions */

struct ub_event_base* comm_base_internal(struct comm_base* b)
{
	return b->eb->base;
}