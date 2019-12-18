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
typedef  int /*<<< orphan*/  uint32_t ;
struct mbuf {int dummy; } ;
struct lro_ctrl {int dummy; } ;

/* Variables and functions */
 int tcp_lro_rx2 (struct lro_ctrl*,struct mbuf*,int /*<<< orphan*/ ,int) ; 

int
tcp_lro_rx(struct lro_ctrl *lc, struct mbuf *m, uint32_t csum)
{

	return tcp_lro_rx2(lc, m, csum, 1);
}