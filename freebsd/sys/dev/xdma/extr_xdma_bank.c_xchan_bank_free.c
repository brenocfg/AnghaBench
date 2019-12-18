#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  xr_mem; } ;
typedef  TYPE_1__ xdma_channel_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_XDMA ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
xchan_bank_free(xdma_channel_t *xchan)
{

	free(xchan->xr_mem, M_XDMA);

	return (0);
}