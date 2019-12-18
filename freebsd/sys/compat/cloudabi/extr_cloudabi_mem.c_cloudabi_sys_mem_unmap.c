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
struct thread {int dummy; } ;
struct cloudabi_sys_mem_unmap_args {int /*<<< orphan*/  mapping_len; scalar_t__ mapping; } ;

/* Variables and functions */
 int kern_munmap (struct thread*,uintptr_t,int /*<<< orphan*/ ) ; 

int
cloudabi_sys_mem_unmap(struct thread *td,
    struct cloudabi_sys_mem_unmap_args *uap)
{

	return (kern_munmap(td, (uintptr_t)uap->mapping, uap->mapping_len));
}