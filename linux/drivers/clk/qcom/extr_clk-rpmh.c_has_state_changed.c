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
typedef  int /*<<< orphan*/  u32 ;
struct clk_rpmh {int last_sent_aggr_state; int aggr_state; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool has_state_changed(struct clk_rpmh *c, u32 state)
{
	return (c->last_sent_aggr_state & BIT(state))
		!= (c->aggr_state & BIT(state));
}