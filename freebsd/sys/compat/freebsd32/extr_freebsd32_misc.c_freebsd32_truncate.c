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
struct freebsd32_truncate_args {int /*<<< orphan*/  length; int /*<<< orphan*/  path; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAIR32TO64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UIO_USERSPACE ; 
 int kern_truncate (struct thread*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  off_t ; 

int
freebsd32_truncate(struct thread *td, struct freebsd32_truncate_args *uap)
{

	return (kern_truncate(td, uap->path, UIO_USERSPACE,
	    PAIR32TO64(off_t, uap->length)));
}