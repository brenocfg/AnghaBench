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

/* Variables and functions */
 int /*<<< orphan*/  amd64_syscall_ret_flush_l1d_inline (int) ; 

void
amd64_syscall_ret_flush_l1d(int error)
{

	amd64_syscall_ret_flush_l1d_inline(error);
}