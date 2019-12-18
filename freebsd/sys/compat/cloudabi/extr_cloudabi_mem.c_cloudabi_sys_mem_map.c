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
struct cloudabi_sys_mem_map_args {int flags; int /*<<< orphan*/  off; int /*<<< orphan*/  fd; int /*<<< orphan*/  len; scalar_t__ addr; int /*<<< orphan*/  prot; } ;

/* Variables and functions */
 int CLOUDABI_MAP_ANON ; 
 int CLOUDABI_MAP_FIXED ; 
 int CLOUDABI_MAP_PRIVATE ; 
 int CLOUDABI_MAP_SHARED ; 
 int MAP_ANON ; 
 int MAP_FIXED ; 
 int MAP_PRIVATE ; 
 int MAP_SHARED ; 
 int convert_mprot (int /*<<< orphan*/ ,int*) ; 
 int kern_mmap (struct thread*,uintptr_t,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
cloudabi_sys_mem_map(struct thread *td, struct cloudabi_sys_mem_map_args *uap)
{
	int error, flags, prot;

	/* Translate flags. */
	flags = 0;
	if (uap->flags & CLOUDABI_MAP_ANON)
		flags |= MAP_ANON;
	if (uap->flags & CLOUDABI_MAP_FIXED)
		flags |= MAP_FIXED;
	if (uap->flags & CLOUDABI_MAP_PRIVATE)
		flags |= MAP_PRIVATE;
	if (uap->flags & CLOUDABI_MAP_SHARED)
		flags |= MAP_SHARED;

	/* Translate protection. */
	error = convert_mprot(uap->prot, &prot);
	if (error != 0)
		return (error);

	return (kern_mmap(td, (uintptr_t)uap->addr, uap->len, prot, flags,
	    uap->fd, uap->off));
}