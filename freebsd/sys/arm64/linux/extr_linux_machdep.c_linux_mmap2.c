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
struct linux_mmap2_args {int /*<<< orphan*/  pgoff; int /*<<< orphan*/  fd; int /*<<< orphan*/  flags; int /*<<< orphan*/  prot; int /*<<< orphan*/  len; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIN_SDT_PROBE0 (int /*<<< orphan*/ ,int (*) (struct thread*,struct linux_mmap2_args*),int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PTROUT (int /*<<< orphan*/ ) ; 
 int linux_mmap_common (struct thread*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  machdep ; 
 int /*<<< orphan*/  todo ; 

int
linux_mmap2(struct thread *td, struct linux_mmap2_args *uap)
{

	LIN_SDT_PROBE0(machdep, linux_mmap2, todo);
	return (linux_mmap_common(td, PTROUT(uap->addr), uap->len, uap->prot,
	    uap->flags, uap->fd, uap->pgoff));
}