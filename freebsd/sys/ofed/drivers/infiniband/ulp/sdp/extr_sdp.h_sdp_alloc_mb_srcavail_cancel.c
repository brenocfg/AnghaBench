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
 int /*<<< orphan*/  SDP_MID_SRCAVAIL_CANCEL ; 
 struct mbuf* sdp_alloc_mb (struct socket*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline struct mbuf *
sdp_alloc_mb_srcavail_cancel(struct socket *sk, int wait)
{
	return sdp_alloc_mb(sk, SDP_MID_SRCAVAIL_CANCEL, 0, wait);
}