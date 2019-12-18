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
typedef  int /*<<< orphan*/  bus_size_t ;
typedef  int /*<<< orphan*/  bus_dma_segment_t ;

/* Variables and functions */
 int /*<<< orphan*/  cesa_create_chain_cb (void*,int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static void
cesa_create_chain_cb2(void *arg, bus_dma_segment_t *segs, int nseg,
    bus_size_t size, int error)
{

	cesa_create_chain_cb(arg, segs, nseg, error);
}