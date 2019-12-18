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
struct pcm_channel {int /*<<< orphan*/  lock; int /*<<< orphan*/  intr_cv; int /*<<< orphan*/  cv; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHN_BROADCAST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CHN_LOCKASSERT (struct pcm_channel*) ; 
 int /*<<< orphan*/  cv_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_mtxfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
chn_lockdestroy(struct pcm_channel *c)
{
	CHN_LOCKASSERT(c);

	CHN_BROADCAST(&c->cv);
	CHN_BROADCAST(&c->intr_cv);

	cv_destroy(&c->cv);
	cv_destroy(&c->intr_cv);

	snd_mtxfree(c->lock);
}