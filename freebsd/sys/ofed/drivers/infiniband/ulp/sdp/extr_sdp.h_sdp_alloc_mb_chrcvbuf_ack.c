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
struct sdp_chrecvbuf {int /*<<< orphan*/  size; } ;
struct mbuf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SDP_MID_CHRCVBUF_ACK ; 
 int /*<<< orphan*/  htonl (int) ; 
 scalar_t__ mb_put (struct mbuf*,int) ; 
 struct mbuf* sdp_alloc_mb (struct socket*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static inline struct mbuf *
sdp_alloc_mb_chrcvbuf_ack(struct socket *sk, int size, int wait)
{
	struct mbuf *mb;
	struct sdp_chrecvbuf *resp_size;

	mb = sdp_alloc_mb(sk, SDP_MID_CHRCVBUF_ACK, sizeof(*resp_size), wait);
	if (mb == NULL)
		return (NULL);
	resp_size = (struct sdp_chrecvbuf *)mb_put(mb, sizeof *resp_size);
	resp_size->size = htonl(size);

	return mb;
}