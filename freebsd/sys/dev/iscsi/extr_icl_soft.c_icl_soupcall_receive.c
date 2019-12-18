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
struct icl_conn {int /*<<< orphan*/  ic_receive_cv; } ;

/* Variables and functions */
 int SU_OK ; 
 int /*<<< orphan*/  cv_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  soreadable (struct socket*) ; 

__attribute__((used)) static int
icl_soupcall_receive(struct socket *so, void *arg, int waitflag)
{
	struct icl_conn *ic;

	if (!soreadable(so))
		return (SU_OK);

	ic = arg;
	cv_signal(&ic->ic_receive_cv);
	return (SU_OK);
}