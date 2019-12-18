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
struct sdp_sock {int dummy; } ;

/* Variables and functions */
 scalar_t__ sdp_post_recv (struct sdp_sock*) ; 
 scalar_t__ sdp_post_recvs_needed (struct sdp_sock*) ; 

__attribute__((used)) static inline void
sdp_post_recvs(struct sdp_sock *ssk)
{

	while (sdp_post_recvs_needed(ssk))
		if (sdp_post_recv(ssk))
			return;
}