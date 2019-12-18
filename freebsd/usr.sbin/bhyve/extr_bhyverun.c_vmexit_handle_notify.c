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
typedef  int /*<<< orphan*/  uint32_t ;
struct vmctx {int dummy; } ;
struct vm_exit {int dummy; } ;

/* Variables and functions */
 int VMEXIT_CONTINUE ; 

__attribute__((used)) static int
vmexit_handle_notify(struct vmctx *ctx, struct vm_exit *vme, int *pvcpu,
		     uint32_t eax)
{
#if BHYVE_DEBUG
	/*
	 * put guest-driven debug here
	 */
#endif
	return (VMEXIT_CONTINUE);
}