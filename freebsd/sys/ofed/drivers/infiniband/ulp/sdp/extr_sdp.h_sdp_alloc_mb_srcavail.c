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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct socket {int dummy; } ;
struct sdp_srcah {int /*<<< orphan*/  vaddr; void* rkey; void* len; } ;
struct mbuf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SDP_MID_SRCAVAIL ; 
 int /*<<< orphan*/  cpu_to_be64 (int /*<<< orphan*/ ) ; 
 void* htonl (int /*<<< orphan*/ ) ; 
 scalar_t__ mb_put (struct mbuf*,int) ; 
 struct mbuf* sdp_alloc_mb (struct socket*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static inline struct mbuf *
sdp_alloc_mb_srcavail(struct socket *sk, u32 len, u32 rkey, u64 vaddr, int wait)
{
	struct mbuf *mb;
	struct sdp_srcah *srcah;

	mb = sdp_alloc_mb(sk, SDP_MID_SRCAVAIL, sizeof(*srcah), wait);
	if (mb == NULL)
		return (NULL);
	srcah = (struct sdp_srcah *)mb_put(mb, sizeof(*srcah));
	srcah->len = htonl(len);
	srcah->rkey = htonl(rkey);
	srcah->vaddr = cpu_to_be64(vaddr);

	return mb;
}