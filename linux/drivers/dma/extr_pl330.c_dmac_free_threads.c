#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct pl330_thread {int dummy; } ;
struct TYPE_2__ {int num_chan; } ;
struct pl330_dmac {struct pl330_thread* channels; TYPE_1__ pcfg; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct pl330_thread*) ; 
 int /*<<< orphan*/  pl330_release_channel (struct pl330_thread*) ; 

__attribute__((used)) static int dmac_free_threads(struct pl330_dmac *pl330)
{
	struct pl330_thread *thrd;
	int i;

	/* Release Channel threads */
	for (i = 0; i < pl330->pcfg.num_chan; i++) {
		thrd = &pl330->channels[i];
		pl330_release_channel(thrd);
	}

	/* Free memory */
	kfree(pl330->channels);

	return 0;
}