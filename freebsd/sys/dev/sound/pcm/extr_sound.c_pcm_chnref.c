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
struct pcm_channel {int refcount; int /*<<< orphan*/  parentsnddev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHN_LOCKASSERT (struct pcm_channel*) ; 
 int /*<<< orphan*/  PCM_BUSYASSERT (int /*<<< orphan*/ ) ; 

int
pcm_chnref(struct pcm_channel *c, int ref)
{
	PCM_BUSYASSERT(c->parentsnddev);
	CHN_LOCKASSERT(c);

	c->refcount += ref;

	return (c->refcount);
}