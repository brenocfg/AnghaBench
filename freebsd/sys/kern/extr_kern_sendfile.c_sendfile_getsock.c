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
struct socket {scalar_t__ so_type; } ;
struct file {struct socket* f_data; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOTCONN ; 
 scalar_t__ SOCK_STREAM ; 
 scalar_t__ SOLISTENING (struct socket*) ; 
 int /*<<< orphan*/  cap_send_rights ; 
 int getsock_cap (struct thread*,int,int /*<<< orphan*/ *,struct file**,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
sendfile_getsock(struct thread *td, int s, struct file **sock_fp,
    struct socket **so)
{
	int error;

	*sock_fp = NULL;
	*so = NULL;

	/*
	 * The socket must be a stream socket and connected.
	 */
	error = getsock_cap(td, s, &cap_send_rights,
	    sock_fp, NULL, NULL);
	if (error != 0)
		return (error);
	*so = (*sock_fp)->f_data;
	if ((*so)->so_type != SOCK_STREAM)
		return (EINVAL);
	if (SOLISTENING(*so))
		return (ENOTCONN);
	return (0);
}