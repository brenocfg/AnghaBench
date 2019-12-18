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
struct rt_spare {int dummy; } ;
struct rt_entry {int dummy; } ;

/* Variables and functions */
 struct rt_spare rts_empty ; 
 int /*<<< orphan*/  trace_upslot (struct rt_entry*,struct rt_spare*,struct rt_spare*) ; 

void
rts_delete(struct rt_entry *rt,
	   struct rt_spare *rts)
{
	trace_upslot(rt, rts, &rts_empty);
	*rts = rts_empty;
}