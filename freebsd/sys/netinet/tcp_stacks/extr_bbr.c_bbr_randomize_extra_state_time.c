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
typedef  int uint32_t ;
struct TYPE_2__ {int rc_level_state_extra; } ;
struct tcp_bbr {TYPE_1__ r_ctl; } ;

/* Variables and functions */
 int arc4random_uniform (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bbr_rand_ot ; 

__attribute__((used)) static void
bbr_randomize_extra_state_time(struct tcp_bbr *bbr)
{
	uint32_t ran, deduct;
	
	ran = arc4random_uniform(bbr_rand_ot);
	if (ran) {
		deduct = bbr->r_ctl.rc_level_state_extra / ran;
		bbr->r_ctl.rc_level_state_extra -= deduct;
	}
}