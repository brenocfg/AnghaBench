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
struct dmaengine_desc_callback {int /*<<< orphan*/  callback_param; int /*<<< orphan*/  callback_result; int /*<<< orphan*/  callback; } ;
struct dma_async_tx_descriptor {int /*<<< orphan*/  callback_param; int /*<<< orphan*/  callback_result; int /*<<< orphan*/  callback; } ;

/* Variables and functions */

__attribute__((used)) static inline void
dmaengine_desc_get_callback(struct dma_async_tx_descriptor *tx,
			    struct dmaengine_desc_callback *cb)
{
	cb->callback = tx->callback;
	cb->callback_result = tx->callback_result;
	cb->callback_param = tx->callback_param;
}