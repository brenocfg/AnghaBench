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
struct socket {int dummy; } ;
struct sdp_rrch {int /*<<< orphan*/  len; } ;
struct mbuf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SDP_MID_RDMARDCOMPL ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 scalar_t__ mb_put (struct mbuf*,int) ; 
 struct mbuf* sdp_alloc_mb (struct socket*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static inline struct mbuf *
sdp_alloc_mb_rdmardcompl(struct socket *sk, u32 len, int wait)
{
	struct mbuf *mb;
	struct sdp_rrch *rrch;

	mb = sdp_alloc_mb(sk, SDP_MID_RDMARDCOMPL, sizeof(*rrch), wait);
	if (mb == NULL)
		return (NULL);
	rrch = (struct sdp_rrch *)mb_put(mb, sizeof(*rrch));
	rrch->len = htonl(len);

	return mb;
}