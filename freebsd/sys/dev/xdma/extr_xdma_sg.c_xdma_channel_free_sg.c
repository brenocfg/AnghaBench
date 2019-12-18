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
typedef  int /*<<< orphan*/  xdma_channel_t ;

/* Variables and functions */
 int /*<<< orphan*/  xchan_bank_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xchan_bufs_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xchan_sglist_free (int /*<<< orphan*/ *) ; 

void
xdma_channel_free_sg(xdma_channel_t *xchan)
{

	xchan_bufs_free(xchan);
	xchan_sglist_free(xchan);
	xchan_bank_free(xchan);
}