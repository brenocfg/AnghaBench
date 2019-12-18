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
struct TYPE_2__ {scalar_t__ md_tp; } ;
struct thread {TYPE_1__ td_md; } ;
typedef  scalar_t__ register_t ;

/* Variables and functions */
 scalar_t__ ARM_TP_ADDRESS ; 
 int /*<<< orphan*/  set_tls (void*) ; 

__attribute__((used)) static int
arm32_set_tp(struct thread *td, void *args)
{

#if __ARM_ARCH >= 6
	set_tls(args);
#else
	td->td_md.md_tp = (register_t)args;
	*(register_t *)ARM_TP_ADDRESS = (register_t)args;
#endif
	return (0);
}