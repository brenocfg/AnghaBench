#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int cch_fd; int /*<<< orphan*/  cch_flags; } ;
typedef  TYPE_1__ cap_channel_t ;

/* Variables and functions */
 TYPE_1__* cap_init () ; 
 int dup (int) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 

__attribute__((used)) static inline cap_channel_t *
cap_clone(const cap_channel_t *chan)
{
	cap_channel_t *newchan;

	newchan = cap_init();
	if (newchan == NULL) {
		return (NULL);
	}

	if (chan->cch_fd == -1) {
		newchan->cch_fd = -1;
	} else {
		newchan->cch_fd = dup(chan->cch_fd);
		if (newchan->cch_fd < 0) {
			free(newchan);
			newchan = NULL;
		}
	}
	newchan->cch_flags = chan->cch_flags;

	return (newchan);
}