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
struct pcm_channel {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHN_LOCK (struct pcm_channel*) ; 
 scalar_t__ CHN_LOCKOWNED (struct pcm_channel*) ; 
 int /*<<< orphan*/  CHN_UNLOCK (struct pcm_channel*) ; 
 int /*<<< orphan*/  chn_intr_locked (struct pcm_channel*) ; 

void
chn_intr(struct pcm_channel *c)
{

	if (CHN_LOCKOWNED(c)) {
		chn_intr_locked(c);
		return;
	}

	CHN_LOCK(c);
	chn_intr_locked(c);
	CHN_UNLOCK(c);
}