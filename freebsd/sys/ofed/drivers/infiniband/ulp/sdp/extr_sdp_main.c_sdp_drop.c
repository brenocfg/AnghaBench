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
struct socket {int so_error; } ;
struct sdp_sock {int softerror; int /*<<< orphan*/  state; struct socket* socket; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  SDP_WLOCK_ASSERT (struct sdp_sock*) ; 
 scalar_t__ TCPS_HAVERCVDSYN (int /*<<< orphan*/ ) ; 
 struct sdp_sock* sdp_closed (struct sdp_sock*) ; 
 int /*<<< orphan*/  sdp_output_reset (struct sdp_sock*) ; 

__attribute__((used)) static struct sdp_sock *
sdp_drop(struct sdp_sock *ssk, int errno)
{
	struct socket *so;

	SDP_WLOCK_ASSERT(ssk);
	so = ssk->socket;
	if (TCPS_HAVERCVDSYN(ssk->state))
		sdp_output_reset(ssk);
	if (errno == ETIMEDOUT && ssk->softerror)
		errno = ssk->softerror;
	so->so_error = errno;
	return (sdp_closed(ssk));
}