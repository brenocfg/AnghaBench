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
struct vmctx {int dummy; } ;
struct vm_exit {int dummy; } ;

/* Variables and functions */
 int VMEXIT_CONTINUE ; 
 int /*<<< orphan*/  gdb_cpu_suspend (int) ; 

__attribute__((used)) static int
vmexit_debug(struct vmctx *ctx, struct vm_exit *vmexit, int *pvcpu)
{

	gdb_cpu_suspend(*pvcpu);
	return (VMEXIT_CONTINUE);
}