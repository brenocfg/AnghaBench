#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_2__ {scalar_t__ rc_lt_bw; } ;
struct tcp_bbr {TYPE_1__ r_ctl; scalar_t__ rc_lt_use_bw; scalar_t__ rc_lt_is_sampling; } ;

/* Variables and functions */
 int /*<<< orphan*/  bbr_reset_lt_bw_interval (struct tcp_bbr*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
bbr_reset_lt_bw_sampling(struct tcp_bbr *bbr, uint32_t cts)
{
	bbr->rc_lt_is_sampling = 0;
	bbr->rc_lt_use_bw = 0;
	bbr->r_ctl.rc_lt_bw = 0;
	bbr_reset_lt_bw_interval(bbr, cts);
}