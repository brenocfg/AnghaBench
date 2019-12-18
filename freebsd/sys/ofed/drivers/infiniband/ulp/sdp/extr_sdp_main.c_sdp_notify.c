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
struct sdp_sock {int flags; scalar_t__ state; int softerror; } ;

/* Variables and functions */
 int EHOSTDOWN ; 
 int EHOSTUNREACH ; 
 int ENETUNREACH ; 
 int SDP_DROPPED ; 
 int SDP_TIMEWAIT ; 
 int /*<<< orphan*/  SDP_WLOCK_ASSERT (struct sdp_sock*) ; 
 scalar_t__ TCPS_ESTABLISHED ; 
 struct sdp_sock* sdp_drop (struct sdp_sock*,int) ; 

struct sdp_sock *
sdp_notify(struct sdp_sock *ssk, int error)
{

	SDP_WLOCK_ASSERT(ssk);

	if ((ssk->flags & SDP_TIMEWAIT) ||
	    (ssk->flags & SDP_DROPPED))
		return (ssk);

	/*
	 * Ignore some errors if we are hooked up.
	 */
	if (ssk->state == TCPS_ESTABLISHED &&
	    (error == EHOSTUNREACH || error == ENETUNREACH ||
	     error == EHOSTDOWN))
		return (ssk);
	ssk->softerror = error;
	return sdp_drop(ssk, error);
}