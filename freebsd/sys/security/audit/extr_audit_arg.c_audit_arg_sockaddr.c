#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct thread {int dummy; } ;
struct sockaddr_un {int /*<<< orphan*/  sun_path; } ;
struct sockaddr {int sa_family; int /*<<< orphan*/  sa_len; } ;
struct TYPE_2__ {int /*<<< orphan*/  ar_arg_sockaddr; } ;
struct kaudit_record {TYPE_1__ k_ar; } ;

/* Variables and functions */
#define  AF_INET 130 
#define  AF_INET6 129 
#define  AF_UNIX 128 
 int /*<<< orphan*/  ARG_SADDRINET ; 
 int /*<<< orphan*/  ARG_SADDRINET6 ; 
 int /*<<< orphan*/  ARG_SADDRUNIX ; 
 int /*<<< orphan*/  ARG_SET_VALID (struct kaudit_record*,int /*<<< orphan*/ ) ; 
 int AT_FDCWD ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  audit_arg_atfd1 (int) ; 
 int /*<<< orphan*/  audit_arg_upath1 (struct thread*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcopy (struct sockaddr*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct kaudit_record* currecord () ; 

void
audit_arg_sockaddr(struct thread *td, int dirfd, struct sockaddr *sa)
{
	struct kaudit_record *ar;

	KASSERT(td != NULL, ("audit_arg_sockaddr: td == NULL"));
	KASSERT(sa != NULL, ("audit_arg_sockaddr: sa == NULL"));

	ar = currecord();
	if (ar == NULL)
		return;

	bcopy(sa, &ar->k_ar.ar_arg_sockaddr, sa->sa_len);
	switch (sa->sa_family) {
	case AF_INET:
		ARG_SET_VALID(ar, ARG_SADDRINET);
		break;

	case AF_INET6:
		ARG_SET_VALID(ar, ARG_SADDRINET6);
		break;

	case AF_UNIX:
		if (dirfd != AT_FDCWD)
			audit_arg_atfd1(dirfd);
		audit_arg_upath1(td, dirfd,
		    ((struct sockaddr_un *)sa)->sun_path);
		ARG_SET_VALID(ar, ARG_SADDRUNIX);
		break;
	/* XXXAUDIT: default:? */
	}
}