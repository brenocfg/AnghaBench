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
struct tcphdr {int dummy; } ;
struct tcpcb {int /*<<< orphan*/  t_inpcb; } ;
struct mbuf {int dummy; } ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  INP_WUNLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcp_dropwithreset (struct mbuf*,struct tcphdr*,struct tcpcb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
ctf_do_dropwithreset(struct mbuf *m, struct tcpcb *tp, struct tcphdr *th,
    int32_t rstreason, int32_t tlen)
{
	if (tp != NULL) {
		tcp_dropwithreset(m, th, tp, tlen, rstreason);
		INP_WUNLOCK(tp->t_inpcb);
	} else
		tcp_dropwithreset(m, th, NULL, tlen, rstreason);
}