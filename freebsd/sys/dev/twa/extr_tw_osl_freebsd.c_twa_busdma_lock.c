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
struct mtx {int dummy; } ;
typedef  int bus_dma_lock_op_t ;
typedef  int /*<<< orphan*/  TW_VOID ;

/* Variables and functions */
#define  BUS_DMA_LOCK 129 
#define  BUS_DMA_UNLOCK 128 
 int /*<<< orphan*/  mtx_lock_spin (struct mtx*) ; 
 int /*<<< orphan*/  mtx_unlock_spin (struct mtx*) ; 
 int /*<<< orphan*/  panic (char*,int) ; 

TW_VOID
twa_busdma_lock(TW_VOID *lock_arg, bus_dma_lock_op_t op)
{
	struct mtx	*lock;

	lock = (struct mtx *)lock_arg;
	switch (op) {
	case BUS_DMA_LOCK:
		mtx_lock_spin(lock);
		break;

	case BUS_DMA_UNLOCK:
		mtx_unlock_spin(lock);
		break;

	default:
		panic("Unknown operation 0x%x for twa_busdma_lock!", op);
	}
}