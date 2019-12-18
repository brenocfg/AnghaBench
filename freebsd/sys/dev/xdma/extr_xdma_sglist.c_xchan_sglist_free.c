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
struct TYPE_3__ {int flags; int /*<<< orphan*/  sg; } ;
typedef  TYPE_1__ xdma_channel_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_XDMA ; 
 int XCHAN_SGLIST_ALLOCATED ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
xchan_sglist_free(xdma_channel_t *xchan)
{

	if (xchan->flags & XCHAN_SGLIST_ALLOCATED)
		free(xchan->sg, M_XDMA);

	xchan->flags &= ~XCHAN_SGLIST_ALLOCATED;
}