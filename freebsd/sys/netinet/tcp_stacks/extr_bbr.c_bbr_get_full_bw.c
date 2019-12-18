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
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_2__ {int /*<<< orphan*/  rc_delrate; } ;
struct tcp_bbr {TYPE_1__ r_ctl; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_filter_value (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline uint64_t
bbr_get_full_bw(struct tcp_bbr *bbr)
{
	uint64_t bw;

	bw = get_filter_value(&bbr->r_ctl.rc_delrate);

	return (bw);
}