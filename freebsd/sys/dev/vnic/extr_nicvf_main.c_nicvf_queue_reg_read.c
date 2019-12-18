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
typedef  int uint64_t ;
struct nicvf {int /*<<< orphan*/  reg_base; } ;
typedef  scalar_t__ bus_space_handle_t ;

/* Variables and functions */
 int NIC_Q_NUM_SHIFT ; 
 int bus_read_8 (int /*<<< orphan*/ ,scalar_t__) ; 

uint64_t
nicvf_queue_reg_read(struct nicvf *nic, bus_space_handle_t offset,
    uint64_t qidx)
{

	return (bus_read_8(nic->reg_base, offset + (qidx << NIC_Q_NUM_SHIFT)));
}