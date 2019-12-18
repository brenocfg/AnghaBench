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
typedef  int /*<<< orphan*/  vm_offset_t ;
typedef  int /*<<< orphan*/  u_int ;
struct thread {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ptrace_read_int (struct thread*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static u_int
ptrace_get_usr_int(void* cookie, vm_offset_t offset, u_int* val)
{
	struct thread *td = cookie;
	u_int error;

	error = ptrace_read_int(td, offset, val);

	return (error);
}