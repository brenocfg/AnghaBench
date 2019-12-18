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
struct qce_dma_data {int /*<<< orphan*/  txchan; int /*<<< orphan*/  rxchan; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_async_issue_pending (int /*<<< orphan*/ ) ; 

void qce_dma_issue_pending(struct qce_dma_data *dma)
{
	dma_async_issue_pending(dma->rxchan);
	dma_async_issue_pending(dma->txchan);
}