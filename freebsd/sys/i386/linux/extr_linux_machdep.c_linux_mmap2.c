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
typedef  int uint64_t ;
typedef  scalar_t__ uint32_t ;
struct thread {int dummy; } ;
struct linux_mmap2_args {scalar_t__ pgoff; int /*<<< orphan*/  fd; int /*<<< orphan*/  flags; int /*<<< orphan*/  prot; int /*<<< orphan*/  len; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int PAGE_SIZE ; 
 int linux_mmap_common (struct thread*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int
linux_mmap2(struct thread *td, struct linux_mmap2_args *args)
{

	return (linux_mmap_common(td, args->addr, args->len, args->prot,
		args->flags, args->fd, (uint64_t)(uint32_t)args->pgoff *
		PAGE_SIZE));
}