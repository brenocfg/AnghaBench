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
struct timeval {int dummy; } ;
struct tcpcb {int /*<<< orphan*/  t_inpcb; scalar_t__ t_fb_ptr; } ;
struct tcp_bbr {int dummy; } ;
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  INP_WLOCK_ASSERT (int /*<<< orphan*/ ) ; 
 int bbr_output_wtime (struct tcpcb*,struct timeval*) ; 
 int /*<<< orphan*/  tcp_get_usecs (struct timeval*) ; 

__attribute__((used)) static int
bbr_output(struct tcpcb *tp)
{
	int32_t ret;
	struct timeval tv;
	struct tcp_bbr *bbr;

	bbr = (struct tcp_bbr *)tp->t_fb_ptr;
	INP_WLOCK_ASSERT(tp->t_inpcb);
	(void)tcp_get_usecs(&tv);
	ret = bbr_output_wtime(tp, &tv);
	return (ret);
}