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
struct socket {int dummy; } ;
struct icl_conn {int ic_check_send_space; int /*<<< orphan*/  ic_send_cv; } ;

/* Variables and functions */
 int /*<<< orphan*/  ICL_CONN_LOCK (struct icl_conn*) ; 
 int /*<<< orphan*/  ICL_CONN_UNLOCK (struct icl_conn*) ; 
 int SU_OK ; 
 int /*<<< orphan*/  cv_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sowriteable (struct socket*) ; 

__attribute__((used)) static int
icl_soupcall_send(struct socket *so, void *arg, int waitflag)
{
	struct icl_conn *ic;

	if (!sowriteable(so))
		return (SU_OK);

	ic = arg;

	ICL_CONN_LOCK(ic);
	ic->ic_check_send_space = true;
	ICL_CONN_UNLOCK(ic);

	cv_signal(&ic->ic_send_cv);

	return (SU_OK);
}