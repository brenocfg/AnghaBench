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
struct TYPE_2__ {scalar_t__ trigger_at; } ;
typedef  TYPE_1__ Timer ;

/* Variables and functions */

__attribute__((used)) static int
compare_timers(const void *a_, const void *b_) {
    const Timer *a = (const Timer*)a_, *b = (const Timer*)b_;
    return (a->trigger_at > b->trigger_at) ? 1 : (a->trigger_at < b->trigger_at) ? -1 : 0;
}