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
struct sdp_sock {int /*<<< orphan*/  srcavail_cancel_work; int /*<<< orphan*/  socket; } ;
struct mbuf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SDP_SRCAVAIL_CANCEL_TIMEOUT ; 
 int /*<<< orphan*/  mb_entail (struct socket*,struct sdp_sock*,struct mbuf*) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct mbuf* sdp_alloc_mb_srcavail_cancel (struct socket*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdp_dbg_data (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  sdp_post_sends (struct sdp_sock*,int /*<<< orphan*/ ) ; 
 struct sdp_sock* sdp_sk (struct socket*) ; 

__attribute__((used)) static int sdp_post_srcavail_cancel(struct socket *sk)
{
	struct sdp_sock *ssk = sdp_sk(sk);
	struct mbuf *mb;

	sdp_dbg_data(ssk->socket, "Posting srcavail cancel\n");

	mb = sdp_alloc_mb_srcavail_cancel(sk, 0);
	mb_entail(sk, ssk, mb);

	sdp_post_sends(ssk, 0);

	schedule_delayed_work(&ssk->srcavail_cancel_work,
			SDP_SRCAVAIL_CANCEL_TIMEOUT);

	return 0;
}