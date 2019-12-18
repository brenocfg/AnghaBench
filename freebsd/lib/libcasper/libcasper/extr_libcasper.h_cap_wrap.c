#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int cch_fd; int cch_flags; } ;
typedef  TYPE_1__ cap_channel_t ;

/* Variables and functions */
 TYPE_1__* cap_init () ; 

__attribute__((used)) static inline cap_channel_t *
cap_wrap(int sock, int flags)
{
	cap_channel_t *chan;

	chan = cap_init();
	if (chan != NULL) {
		chan->cch_fd = sock;
		chan->cch_flags = flags;
	}
	return (chan);
}