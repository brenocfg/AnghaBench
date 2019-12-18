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
struct sockopt {int dummy; } ;
struct socket {int so_options; int /*<<< orphan*/ * sol_accept_filter_str; TYPE_1__* sol_accept_filter; } ;
struct accept_filter_arg {int /*<<< orphan*/  af_arg; int /*<<< orphan*/  af_name; } ;
struct TYPE_2__ {int /*<<< orphan*/ * accf_name; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  M_TEMP ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  SOCK_LOCK (struct socket*) ; 
 int /*<<< orphan*/  SOCK_UNLOCK (struct socket*) ; 
 int SO_ACCEPTCONN ; 
 int /*<<< orphan*/  free (struct accept_filter_arg*,int /*<<< orphan*/ ) ; 
 struct accept_filter_arg* malloc (int,int /*<<< orphan*/ ,int) ; 
 int sooptcopyout (struct sockopt*,struct accept_filter_arg*,int) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int
accept_filt_getopt(struct socket *so, struct sockopt *sopt)
{
	struct accept_filter_arg *afap;
	int error;

	error = 0;
	afap = malloc(sizeof(*afap), M_TEMP, M_WAITOK | M_ZERO);
	SOCK_LOCK(so);
	if ((so->so_options & SO_ACCEPTCONN) == 0) {
		error = EINVAL;
		goto out;
	}
	if (so->sol_accept_filter == NULL) {
		error = EINVAL;
		goto out;
	}
	strcpy(afap->af_name, so->sol_accept_filter->accf_name);
	if (so->sol_accept_filter_str != NULL)
		strcpy(afap->af_arg, so->sol_accept_filter_str);
out:
	SOCK_UNLOCK(so);
	if (error == 0)
		error = sooptcopyout(sopt, afap, sizeof(*afap));
	free(afap, M_TEMP);
	return (error);
}