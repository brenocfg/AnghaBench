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
struct pcm_channel {int pid; int /*<<< orphan*/  comm; int /*<<< orphan*/  flags; int /*<<< orphan*/  parentsnddev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHN_COMM_UNUSED ; 
 int /*<<< orphan*/  CHN_F_BUSY ; 
 int /*<<< orphan*/  CHN_LOCKASSERT (struct pcm_channel*) ; 
 int /*<<< orphan*/  CHN_UNLOCK (struct pcm_channel*) ; 
 int /*<<< orphan*/  PCM_BUSYASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int
pcm_chnrelease(struct pcm_channel *c)
{
	PCM_BUSYASSERT(c->parentsnddev);
	CHN_LOCKASSERT(c);

	c->flags &= ~CHN_F_BUSY;
	c->pid = -1;
	strlcpy(c->comm, CHN_COMM_UNUSED, sizeof(c->comm));
	CHN_UNLOCK(c);

	return (0);
}