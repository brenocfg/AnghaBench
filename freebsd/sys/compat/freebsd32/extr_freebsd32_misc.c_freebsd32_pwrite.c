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
struct freebsd32_pwrite_args {int /*<<< orphan*/  offset; int /*<<< orphan*/  nbyte; int /*<<< orphan*/  buf; int /*<<< orphan*/  fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAIR32TO64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int kern_pwrite (struct thread*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  off_t ; 

int
freebsd32_pwrite(struct thread *td, struct freebsd32_pwrite_args *uap)
{

	return (kern_pwrite(td, uap->fd, uap->buf, uap->nbyte,
	    PAIR32TO64(off_t, uap->offset)));
}