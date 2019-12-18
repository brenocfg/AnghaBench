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
struct thread {int* td_retval; } ;
struct cloudabi_sys_fd_create2_args {int type; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_UNIX ; 
#define  CLOUDABI_FILETYPE_SOCKET_DGRAM 129 
#define  CLOUDABI_FILETYPE_SOCKET_STREAM 128 
 int EINVAL ; 
 int SOCK_DGRAM ; 
 int SOCK_STREAM ; 
 int kern_socketpair (struct thread*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int*) ; 

int
cloudabi_sys_fd_create2(struct thread *td,
    struct cloudabi_sys_fd_create2_args *uap)
{
	int fds[2];
	int error, type;

	switch (uap->type) {
	case CLOUDABI_FILETYPE_SOCKET_DGRAM:
		type = SOCK_DGRAM;
		break;
	case CLOUDABI_FILETYPE_SOCKET_STREAM:
		type = SOCK_STREAM;
		break;
	default:
		return (EINVAL);
	}

	error = kern_socketpair(td, AF_UNIX, type, 0, fds);
	if (error == 0) {
		td->td_retval[0] = fds[0];
		td->td_retval[1] = fds[1];
	}
	return (0);
}