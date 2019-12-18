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
 int /*<<< orphan*/  DBDMA_NEVER ; 
 int /*<<< orphan*/  DBDMA_STOP ; 
 int /*<<< orphan*/  dbdma_insert_command (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
dbdma_insert_stop(dbdma_channel_t *chan, int slot)
{

	dbdma_insert_command(chan, slot, DBDMA_STOP, 0, 0, 0, DBDMA_NEVER,
	    DBDMA_NEVER, DBDMA_NEVER, 0);
}