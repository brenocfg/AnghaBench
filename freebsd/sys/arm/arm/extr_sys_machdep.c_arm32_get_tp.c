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
struct thread {void** td_retval; } ;
typedef  void* register_t ;

/* Variables and functions */
 scalar_t__ ARM_TP_ADDRESS ; 
 scalar_t__ get_tls () ; 

__attribute__((used)) static int
arm32_get_tp(struct thread *td, void *args)
{

#if __ARM_ARCH >= 6
	td->td_retval[0] = (register_t)get_tls();
#else
	td->td_retval[0] = *(register_t *)ARM_TP_ADDRESS;
#endif
	return (0);
}