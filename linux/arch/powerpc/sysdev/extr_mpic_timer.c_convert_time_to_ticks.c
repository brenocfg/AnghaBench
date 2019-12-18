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
typedef  scalar_t__ u64 ;
typedef  scalar_t__ time64_t ;
struct timer_group_priv {scalar_t__ timerfreq; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  ULLONG_MAX ; 
 scalar_t__ div_u64 (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int convert_time_to_ticks(struct timer_group_priv *priv,
		time64_t time, u64 *ticks)
{
	u64 max_value;		/* prevent u64 overflow */

	max_value = div_u64(ULLONG_MAX, priv->timerfreq);

	if (time > max_value)
		return -EINVAL;

	*ticks = (u64)time * (u64)priv->timerfreq;

	return 0;
}