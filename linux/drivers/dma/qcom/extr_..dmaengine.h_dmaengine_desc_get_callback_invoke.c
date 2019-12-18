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
struct dmaengine_result {int dummy; } ;
struct dmaengine_desc_callback {int dummy; } ;
struct dma_async_tx_descriptor {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dmaengine_desc_callback_invoke (struct dmaengine_desc_callback*,struct dmaengine_result const*) ; 
 int /*<<< orphan*/  dmaengine_desc_get_callback (struct dma_async_tx_descriptor*,struct dmaengine_desc_callback*) ; 

__attribute__((used)) static inline void
dmaengine_desc_get_callback_invoke(struct dma_async_tx_descriptor *tx,
				   const struct dmaengine_result *result)
{
	struct dmaengine_desc_callback cb;

	dmaengine_desc_get_callback(tx, &cb);
	dmaengine_desc_callback_invoke(&cb, result);
}