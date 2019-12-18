#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct hostent_data {int dummy; } ;
struct hostent {int dummy; } ;
typedef  TYPE_1__* res_state ;
struct TYPE_6__ {int options; int res_h_errno; } ;

/* Variables and functions */
 int /*<<< orphan*/  NETDB_INTERNAL ; 
 int RES_INIT ; 
 int /*<<< orphan*/  RES_SET_H_ERRNO (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int RES_USE_INET6 ; 
 scalar_t__ __copy_hostent (struct hostent*,struct hostent*,char*,size_t) ; 
 struct hostent_data* __hostent_data_init () ; 
 TYPE_1__* __res_state () ; 
 scalar_t__ errno ; 
 scalar_t__ gethostent_p (struct hostent*,struct hostent_data*,int,TYPE_1__*) ; 
 int res_ninit (TYPE_1__*) ; 

int
gethostent_r(struct hostent *hptr, char *buffer, size_t buflen,
    struct hostent **result, int *h_errnop)
{
	struct hostent_data *hed;
	struct hostent he;
	res_state statp;

	statp = __res_state();
	if ((statp->options & RES_INIT) == 0 && res_ninit(statp) == -1) {
		RES_SET_H_ERRNO(statp, NETDB_INTERNAL);
		*h_errnop = statp->res_h_errno;
		return (-1);
	}
	if ((hed = __hostent_data_init()) == NULL) {
		RES_SET_H_ERRNO(statp, NETDB_INTERNAL);
		*h_errnop = statp->res_h_errno;
		return (-1);
	}
	if (gethostent_p(&he, hed, statp->options & RES_USE_INET6, statp) != 0)
		return (-1);
	if (__copy_hostent(&he, hptr, buffer, buflen) != 0) {
		RES_SET_H_ERRNO(statp, NETDB_INTERNAL);
		*h_errnop = statp->res_h_errno;
		return ((errno != 0) ? errno : -1);
	}
	*result = hptr;
	return (0);
}