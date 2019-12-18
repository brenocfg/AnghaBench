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

/* Variables and functions */
 int /*<<< orphan*/  EPOLL_DEF_SZ ; 
 int /*<<< orphan*/  epoll_fd_install (struct thread*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int kern_kqueue (struct thread*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
epoll_create_common(struct thread *td, int flags)
{
	int error;

	error = kern_kqueue(td, flags, NULL);
	if (error != 0)
		return (error);

	epoll_fd_install(td, EPOLL_DEF_SZ, 0);

	return (0);
}