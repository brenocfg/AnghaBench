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
struct efirt_callinfo {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  panic (char*) ; 

int
efi_rt_arch_call(struct efirt_callinfo *ec)
{

	panic("not implemented");
}