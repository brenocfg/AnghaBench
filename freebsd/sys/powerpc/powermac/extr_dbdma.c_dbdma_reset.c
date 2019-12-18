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
typedef  int /*<<< orphan*/  dbdma_channel_t ;

/* Variables and functions */
 int /*<<< orphan*/  dbdma_run (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dbdma_set_current_cmd (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dbdma_stop (int /*<<< orphan*/ *) ; 

void
dbdma_reset(dbdma_channel_t *chan)
{

	dbdma_stop(chan);
	dbdma_set_current_cmd(chan, 0);
	dbdma_run(chan);
}