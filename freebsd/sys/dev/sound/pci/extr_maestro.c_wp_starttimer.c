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
struct agg_info {int dummy; } ;

/* Variables and functions */
 int AGG_RD (struct agg_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  AGG_WR (struct agg_info*,int /*<<< orphan*/ ,int,int) ; 
 int HOSTINT_CTRL_DSOUND_INT_ENABLED ; 
 int /*<<< orphan*/  PORT_HOSTINT_CTRL ; 
 int /*<<< orphan*/  PORT_INT_STAT ; 
 int /*<<< orphan*/  WPREG_TIMER_START ; 
 int /*<<< orphan*/  wp_wrreg (struct agg_info*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
wp_starttimer(struct agg_info *ess)
{
	AGG_WR(ess, PORT_INT_STAT, 1, 2);
	AGG_WR(ess, PORT_HOSTINT_CTRL, HOSTINT_CTRL_DSOUND_INT_ENABLED
	       | AGG_RD(ess, PORT_HOSTINT_CTRL, 2), 2);
	wp_wrreg(ess, WPREG_TIMER_START, 1);
}