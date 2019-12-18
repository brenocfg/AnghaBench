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
struct ptrace_io_desc {int piod_len; void* piod_addr; void* piod_offs; int /*<<< orphan*/  piod_op; } ;
typedef  int /*<<< orphan*/  pid_t ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  PIOD_READ_D ; 
 int /*<<< orphan*/  PT_IO ; 
 scalar_t__ ptrace (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
get_struct(pid_t pid, uintptr_t offset, void *buf, int len)
{
	struct ptrace_io_desc iorequest;

	iorequest.piod_op = PIOD_READ_D;
	iorequest.piod_offs = (void *)offset;
	iorequest.piod_addr = buf;
	iorequest.piod_len = len;
	if (ptrace(PT_IO, pid, (caddr_t)&iorequest, 0) < 0)
		return (-1);
	return (0);
}