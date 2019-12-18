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
struct ena_com_io_sq {scalar_t__ mem_queue_type; int tail; int q_depth; int phase; } ;

/* Variables and functions */
 scalar_t__ ENA_ADMIN_PLACEMENT_POLICY_DEV ; 
 int ENA_COM_OK ; 
 int ena_com_sq_update_llq_tail (struct ena_com_io_sq*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline int ena_com_sq_update_tail(struct ena_com_io_sq *io_sq)
{
	if (io_sq->mem_queue_type == ENA_ADMIN_PLACEMENT_POLICY_DEV)
		return ena_com_sq_update_llq_tail(io_sq);

	io_sq->tail++;

	/* Switch phase bit in case of wrap around */
	if (unlikely((io_sq->tail & (io_sq->q_depth - 1)) == 0))
		io_sq->phase ^= 1;

	return ENA_COM_OK;
}