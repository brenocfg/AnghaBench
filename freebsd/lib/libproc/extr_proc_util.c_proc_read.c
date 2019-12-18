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
struct ptrace_io_desc {size_t piod_len; void* piod_offs; void* piod_addr; int /*<<< orphan*/  piod_op; } ;
struct proc_handle {int dummy; } ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  PIOD_READ_D ; 
 int /*<<< orphan*/  PT_IO ; 
 int /*<<< orphan*/  proc_getpid (struct proc_handle*) ; 
 scalar_t__ ptrace (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
proc_read(struct proc_handle *phdl, void *buf, size_t size, size_t addr)
{
	struct ptrace_io_desc piod;

	if (phdl == NULL)
		return (-1);
	piod.piod_op = PIOD_READ_D;
	piod.piod_len = size;
	piod.piod_addr = (void *)buf;
	piod.piod_offs = (void *)addr;

	if (ptrace(PT_IO, proc_getpid(phdl), (caddr_t)&piod, 0) < 0)
		return (-1);
	return (piod.piod_len);
}