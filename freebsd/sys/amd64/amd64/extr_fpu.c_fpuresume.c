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
typedef  int /*<<< orphan*/  u_long ;

/* Variables and functions */
 int /*<<< orphan*/  XCR0 ; 
 int /*<<< orphan*/  fninit () ; 
 int /*<<< orphan*/  fpurestore (void*) ; 
 int /*<<< orphan*/  load_cr0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  load_xcr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcr0 () ; 
 int /*<<< orphan*/  stop_emulating () ; 
 scalar_t__ use_xsave ; 
 int /*<<< orphan*/  xsave_mask ; 

void
fpuresume(void *addr)
{
	u_long cr0;

	cr0 = rcr0();
	stop_emulating();
	fninit();
	if (use_xsave)
		load_xcr(XCR0, xsave_mask);
	fpurestore(addr);
	load_cr0(cr0);
}