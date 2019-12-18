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
struct TYPE_2__ {scalar_t__ rc_pace_min_segs; } ;
struct tcp_bbr {scalar_t__ rc_last_options; TYPE_1__ r_ctl; } ;
typedef  scalar_t__ int32_t ;

/* Variables and functions */

__attribute__((used)) static inline int32_t
bbr_minseg(struct tcp_bbr *bbr)
{
	return (bbr->r_ctl.rc_pace_min_segs - bbr->rc_last_options);
}