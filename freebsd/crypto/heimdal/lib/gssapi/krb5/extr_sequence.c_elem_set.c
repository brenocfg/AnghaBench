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
struct gss_msg_order {unsigned int jitter_window; int /*<<< orphan*/ * elem; } ;
typedef  int /*<<< orphan*/  OM_uint32 ;

/* Variables and functions */

__attribute__((used)) static void
elem_set(struct gss_msg_order *o, unsigned int slot, OM_uint32 val)
{
    o->elem[slot % o->jitter_window] = val;
}