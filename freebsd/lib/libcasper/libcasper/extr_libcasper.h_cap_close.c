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
struct TYPE_4__ {scalar_t__ cch_fd; } ;
typedef  TYPE_1__ cap_channel_t ;

/* Variables and functions */
 int /*<<< orphan*/  close (scalar_t__) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 

__attribute__((used)) static inline void
cap_close(cap_channel_t *chan)
{

	if (chan->cch_fd >= 0) {
		close(chan->cch_fd);
	}
	free(chan);
}