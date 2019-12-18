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
struct linux_fadvise64_args {int /*<<< orphan*/  len; int /*<<< orphan*/  offset; int /*<<< orphan*/  fd; int /*<<< orphan*/  advice; } ;

/* Variables and functions */
 int EINVAL ; 
 int convert_fadvice (int /*<<< orphan*/ ) ; 
 int kern_posix_fadvise (struct thread*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int
linux_fadvise64(struct thread *td, struct linux_fadvise64_args *args)
{
	int advice;

	advice = convert_fadvice(args->advice);
	if (advice == -1)
		return (EINVAL);
	return (kern_posix_fadvise(td, args->fd, args->offset, args->len,
	    advice));
}