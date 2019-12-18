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
struct dma_async_tx_descriptor {int dummy; } ;
typedef  int /*<<< orphan*/  dma_cookie_t ;

/* Variables and functions */
 int /*<<< orphan*/  dma_cookie_assign (struct dma_async_tx_descriptor*) ; 

__attribute__((used)) static dma_cookie_t cppi41_tx_submit(struct dma_async_tx_descriptor *tx)
{
	dma_cookie_t cookie;

	cookie = dma_cookie_assign(tx);

	return cookie;
}