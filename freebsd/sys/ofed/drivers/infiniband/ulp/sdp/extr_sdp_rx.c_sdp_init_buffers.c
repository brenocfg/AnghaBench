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
typedef  int /*<<< orphan*/  u32 ;
struct sdp_sock {int /*<<< orphan*/  recv_bytes; } ;

/* Variables and functions */
 int /*<<< orphan*/  sdp_get_recv_bytes (struct sdp_sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdp_post_recvs (struct sdp_sock*) ; 

int
sdp_init_buffers(struct sdp_sock *ssk, u32 new_size)
{

	ssk->recv_bytes = sdp_get_recv_bytes(ssk, new_size);
	sdp_post_recvs(ssk);

	return 0;
}