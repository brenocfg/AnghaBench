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
struct mic_dma_chan {int dummy; } ;
struct dma_chan {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mic_dma_chan_uninit (struct mic_dma_chan*) ; 
 int /*<<< orphan*/  mic_dma_drain_chan (struct mic_dma_chan*) ; 
 struct mic_dma_chan* to_mic_dma_chan (struct dma_chan*) ; 

__attribute__((used)) static void mic_dma_free_chan_resources(struct dma_chan *ch)
{
	struct mic_dma_chan *mic_ch = to_mic_dma_chan(ch);
	mic_dma_drain_chan(mic_ch);
	mic_dma_chan_uninit(mic_ch);
}