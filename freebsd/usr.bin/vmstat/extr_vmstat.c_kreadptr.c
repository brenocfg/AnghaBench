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
 int /*<<< orphan*/  kd ; 
 int /*<<< orphan*/  kvm_geterr (int /*<<< orphan*/ ) ; 
 scalar_t__ kvm_read (int /*<<< orphan*/ ,uintptr_t,void*,size_t) ; 
 int /*<<< orphan*/  xo_errx (int,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
kreadptr(uintptr_t addr, void *buf, size_t size)
{

	if ((size_t)kvm_read(kd, addr, buf, size) != size)
		xo_errx(1, "%s", kvm_geterr(kd));
}