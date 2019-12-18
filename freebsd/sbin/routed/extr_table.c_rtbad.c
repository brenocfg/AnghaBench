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
struct rt_spare {int /*<<< orphan*/  rts_metric; } ;
struct rt_entry {int rt_state; struct rt_spare* rt_spares; } ;

/* Variables and functions */
 int /*<<< orphan*/  HOPCNT_INFINITY ; 
 int RS_IF ; 
 int RS_LOCAL ; 
 int RS_STATIC ; 
 int /*<<< orphan*/  rtchange (struct rt_entry*,int,struct rt_spare*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtswitch (struct rt_entry*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
rtbad(struct rt_entry *rt)
{
	struct rt_spare new;

	/* Poison the route */
	new = rt->rt_spares[0];
	new.rts_metric = HOPCNT_INFINITY;
	rtchange(rt, rt->rt_state & ~(RS_IF | RS_LOCAL | RS_STATIC), &new, 0);
	rtswitch(rt, 0);
}