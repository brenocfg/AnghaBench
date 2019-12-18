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
struct systimer {scalar_t__ enabled; } ;
struct eventtimer {struct systimer* et_priv; } ;

/* Variables and functions */

__attribute__((used)) static int
bcm_systimer_stop(struct eventtimer *et)
{
	struct systimer *st = et->et_priv;
	st->enabled = 0;

	return (0);
}