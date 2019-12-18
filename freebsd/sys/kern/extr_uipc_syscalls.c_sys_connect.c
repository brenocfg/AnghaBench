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
struct sockaddr {int dummy; } ;
struct connect_args {int /*<<< orphan*/  s; int /*<<< orphan*/  namelen; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  AT_FDCWD ; 
 int /*<<< orphan*/  M_SONAME ; 
 int /*<<< orphan*/  free (struct sockaddr*,int /*<<< orphan*/ ) ; 
 int getsockaddr (struct sockaddr**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int kern_connectat (struct thread*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sockaddr*) ; 

int
sys_connect(struct thread *td, struct connect_args *uap)
{
	struct sockaddr *sa;
	int error;

	error = getsockaddr(&sa, uap->name, uap->namelen);
	if (error == 0) {
		error = kern_connectat(td, AT_FDCWD, uap->s, sa);
		free(sa, M_SONAME);
	}
	return (error);
}