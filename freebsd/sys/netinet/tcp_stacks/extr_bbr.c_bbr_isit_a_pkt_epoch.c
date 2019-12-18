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
struct TYPE_2__ {int /*<<< orphan*/  rc_pkt_epoch_del; } ;
struct tcp_bbr {int rc_is_pkt_epoch_now; TYPE_1__ r_ctl; } ;
struct bbr_sendmap {int /*<<< orphan*/  r_delivered; } ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 scalar_t__ SEQ_GEQ (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
bbr_isit_a_pkt_epoch(struct tcp_bbr *bbr, uint32_t cts, struct bbr_sendmap *rsm, int32_t line, int32_t cum_acked)
{
	if (SEQ_GEQ(rsm->r_delivered, bbr->r_ctl.rc_pkt_epoch_del)) {
		bbr->rc_is_pkt_epoch_now = 1;
	}
}