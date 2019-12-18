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
typedef  int /*<<< orphan*/  u64 ;
struct mpc52xx_gpt_priv {int dummy; } ;

/* Variables and functions */
 int mpc52xx_gpt_do_start (struct mpc52xx_gpt_priv*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

int mpc52xx_gpt_start_timer(struct mpc52xx_gpt_priv *gpt, u64 period,
                            int continuous)
{
	return mpc52xx_gpt_do_start(gpt, period, continuous, 0);
}