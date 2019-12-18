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
struct sdp_sock {int flags; } ;

/* Variables and functions */
 int ECONNRESET ; 
 int SDP_DROPPED ; 
 int SDP_TIMEWAIT ; 
 int /*<<< orphan*/  SDP_WLOCK (struct sdp_sock*) ; 
 int /*<<< orphan*/  SDP_WUNLOCK (struct sdp_sock*) ; 
 int /*<<< orphan*/  sdp_output_disconnect (struct sdp_sock*) ; 
 struct sdp_sock* sdp_sk (struct socket*) ; 
 int /*<<< orphan*/  sdp_usrclosed (struct sdp_sock*) ; 
 int /*<<< orphan*/  socantsendmore (struct socket*) ; 

__attribute__((used)) static int
sdp_shutdown(struct socket *so)
{
	int error = 0;
	struct sdp_sock *ssk;

	ssk = sdp_sk(so);
	SDP_WLOCK(ssk);
	if (ssk->flags & (SDP_TIMEWAIT | SDP_DROPPED)) {
		error = ECONNRESET;
		goto out;
	}
	socantsendmore(so);
	sdp_usrclosed(ssk);
	if (!(ssk->flags & SDP_DROPPED))
		sdp_output_disconnect(ssk);

out:
	SDP_WUNLOCK(ssk);

	return (error);
}