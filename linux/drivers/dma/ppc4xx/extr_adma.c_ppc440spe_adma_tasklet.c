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
struct ppc440spe_adma_chan {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  SINGLE_DEPTH_NESTING ; 
 int /*<<< orphan*/  __ppc440spe_adma_slot_cleanup (struct ppc440spe_adma_chan*) ; 
 int /*<<< orphan*/  spin_lock_nested (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ppc440spe_adma_tasklet(unsigned long data)
{
	struct ppc440spe_adma_chan *chan = (struct ppc440spe_adma_chan *) data;

	spin_lock_nested(&chan->lock, SINGLE_DEPTH_NESTING);
	__ppc440spe_adma_slot_cleanup(chan);
	spin_unlock(&chan->lock);
}