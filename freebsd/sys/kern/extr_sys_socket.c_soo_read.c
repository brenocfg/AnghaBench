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
struct uio {int dummy; } ;
struct ucred {int dummy; } ;
struct thread {int dummy; } ;
struct socket {int dummy; } ;
struct file {struct socket* f_data; } ;

/* Variables and functions */
 int mac_socket_check_receive (struct ucred*,struct socket*) ; 
 int soreceive (struct socket*,int /*<<< orphan*/ ,struct uio*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
soo_read(struct file *fp, struct uio *uio, struct ucred *active_cred,
    int flags, struct thread *td)
{
	struct socket *so = fp->f_data;
	int error;

#ifdef MAC
	error = mac_socket_check_receive(active_cred, so);
	if (error)
		return (error);
#endif
	error = soreceive(so, 0, uio, 0, 0, 0);
	return (error);
}