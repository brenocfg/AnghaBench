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
struct ucred {int dummy; } ;
struct thread {int dummy; } ;
struct socket {int dummy; } ;
struct file {int /*<<< orphan*/  f_cred; struct socket* f_data; } ;

/* Variables and functions */
 int mac_socket_check_poll (struct ucred*,struct socket*) ; 
 int sopoll (struct socket*,int,int /*<<< orphan*/ ,struct thread*) ; 

__attribute__((used)) static int
soo_poll(struct file *fp, int events, struct ucred *active_cred,
    struct thread *td)
{
	struct socket *so = fp->f_data;
#ifdef MAC
	int error;

	error = mac_socket_check_poll(active_cred, so);
	if (error)
		return (error);
#endif
	return (sopoll(so, events, fp->f_cred, td));
}