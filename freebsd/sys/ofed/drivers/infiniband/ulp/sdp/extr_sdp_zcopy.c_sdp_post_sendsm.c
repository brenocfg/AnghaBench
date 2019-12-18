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
struct mbuf {int dummy; } ;

/* Variables and functions */
 struct mbuf* sdp_alloc_mb_sendsm (struct socket*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdp_post_send (int /*<<< orphan*/ ,struct mbuf*) ; 
 int /*<<< orphan*/  sdp_sk (struct socket*) ; 

int sdp_post_sendsm(struct socket *sk)
{
	struct mbuf *mb = sdp_alloc_mb_sendsm(sk, 0);

	sdp_post_send(sdp_sk(sk), mb);

	return 0;
}