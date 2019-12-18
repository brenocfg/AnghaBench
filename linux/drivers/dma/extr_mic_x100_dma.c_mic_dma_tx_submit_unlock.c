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
struct mic_dma_chan {int /*<<< orphan*/  prep_lock; int /*<<< orphan*/  head; int /*<<< orphan*/  submitted; } ;
struct dma_async_tx_descriptor {int /*<<< orphan*/  cookie; int /*<<< orphan*/  chan; } ;
typedef  int /*<<< orphan*/  dma_cookie_t ;

/* Variables and functions */
 int /*<<< orphan*/  dma_cookie_assign (struct dma_async_tx_descriptor*) ; 
 int /*<<< orphan*/  mic_dma_update_pending (struct mic_dma_chan*) ; 
 int /*<<< orphan*/  smp_wmb () ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 struct mic_dma_chan* to_mic_dma_chan (int /*<<< orphan*/ ) ; 

__attribute__((used)) static dma_cookie_t mic_dma_tx_submit_unlock(struct dma_async_tx_descriptor *tx)
{
	struct mic_dma_chan *mic_ch = to_mic_dma_chan(tx->chan);
	dma_cookie_t cookie;

	dma_cookie_assign(tx);
	cookie = tx->cookie;
	/*
	 * We need an smp write barrier here because another CPU might see
	 * an update to submitted and update h/w head even before we
	 * assigned a cookie to this tx.
	 */
	smp_wmb();
	mic_ch->submitted = mic_ch->head;
	spin_unlock(&mic_ch->prep_lock);
	mic_dma_update_pending(mic_ch);
	return cookie;
}