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
typedef  int u_int ;
struct thread {int /*<<< orphan*/  td_proc; } ;
typedef  scalar_t__ sockaddr ;
struct osockaddr {int /*<<< orphan*/  sa_family; } ;
struct getsockname_args {int /*<<< orphan*/  alen; int /*<<< orphan*/  asa; int /*<<< orphan*/  fdes; } ;
typedef  scalar_t__ socklen_t ;
typedef  int /*<<< orphan*/  len ;

/* Variables and functions */
 int /*<<< orphan*/  M_SONAME ; 
 int /*<<< orphan*/  SV_AOUT ; 
 scalar_t__ SV_PROC_FLAG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int copyin (int /*<<< orphan*/ ,scalar_t__*,int) ; 
 int copyout (scalar_t__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  free (scalar_t__*,int /*<<< orphan*/ ) ; 
 int kern_getsockname (struct thread*,int /*<<< orphan*/ ,scalar_t__**,scalar_t__*) ; 

__attribute__((used)) static int
getsockname1(struct thread *td, struct getsockname_args *uap, int compat)
{
	struct sockaddr *sa;
	socklen_t len;
	int error;

	error = copyin(uap->alen, &len, sizeof(len));
	if (error != 0)
		return (error);

	error = kern_getsockname(td, uap->fdes, &sa, &len);
	if (error != 0)
		return (error);

	if (len != 0) {
#ifdef COMPAT_OLDSOCK
		if (compat && SV_PROC_FLAG(td->td_proc, SV_AOUT))
			((struct osockaddr *)sa)->sa_family = sa->sa_family;
#endif
		error = copyout(sa, uap->asa, (u_int)len);
	}
	free(sa, M_SONAME);
	if (error == 0)
		error = copyout(&len, uap->alen, sizeof(len));
	return (error);
}