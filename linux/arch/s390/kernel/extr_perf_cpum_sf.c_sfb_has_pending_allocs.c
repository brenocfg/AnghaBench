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
struct sf_buffer {int dummy; } ;
struct hw_perf_event {int dummy; } ;

/* Variables and functions */
 scalar_t__ sfb_pending_allocs (struct sf_buffer*,struct hw_perf_event*) ; 

__attribute__((used)) static int sfb_has_pending_allocs(struct sf_buffer *sfb,
				   struct hw_perf_event *hwc)
{
	return sfb_pending_allocs(sfb, hwc) > 0;
}