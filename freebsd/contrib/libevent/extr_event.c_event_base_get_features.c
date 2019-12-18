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
struct event_base {TYPE_1__* evsel; } ;
struct TYPE_2__ {int features; } ;

/* Variables and functions */

int
event_base_get_features(const struct event_base *base)
{
	return base->evsel->features;
}