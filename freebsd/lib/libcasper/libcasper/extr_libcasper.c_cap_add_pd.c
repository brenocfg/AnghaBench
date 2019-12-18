#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int cch_pd; } ;
typedef  TYPE_1__ cap_channel_t ;

/* Variables and functions */
 int /*<<< orphan*/  fd_is_valid (int) ; 

__attribute__((used)) static bool
cap_add_pd(cap_channel_t *chan, int pd)
{

	if (!fd_is_valid(pd))
		return (false);
	chan->cch_pd = pd;
	return (true);
}