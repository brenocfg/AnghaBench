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
struct event_debug_entry {scalar_t__ ptr; } ;

/* Variables and functions */

__attribute__((used)) static inline int
eq_debug_entry(const struct event_debug_entry *a,
    const struct event_debug_entry *b)
{
	return a->ptr == b->ptr;
}