#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  (* message_pass ) (int,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  smp_muxed_ipi_message_pass (int,int) ; 
 TYPE_1__* smp_ops ; 
 int /*<<< orphan*/  stub1 (int,int) ; 

__attribute__((used)) static inline void do_message_pass(int cpu, int msg)
{
	if (smp_ops->message_pass)
		smp_ops->message_pass(cpu, msg);
#ifdef CONFIG_PPC_SMP_MUXED_IPI
	else
		smp_muxed_ipi_message_pass(cpu, msg);
#endif
}