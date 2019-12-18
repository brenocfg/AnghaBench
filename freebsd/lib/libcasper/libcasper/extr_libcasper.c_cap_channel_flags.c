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
struct TYPE_3__ {int cch_flags; } ;
typedef  TYPE_1__ cap_channel_t ;

/* Variables and functions */

int
cap_channel_flags(const cap_channel_t *chan)
{

	return (chan->cch_flags);
}