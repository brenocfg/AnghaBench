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
typedef  int uint64_t ;
typedef  scalar_t__ uint32_t ;
typedef  int uint16_t ;
struct tcp_bbr {int dummy; } ;

/* Variables and functions */
 scalar_t__ BBR_UNIT ; 
 scalar_t__ USECS_IN_SECOND ; 
 int bbr_gain_adjust (struct tcp_bbr*,int) ; 

__attribute__((used)) static uint32_t
bbr_get_pacing_length(struct tcp_bbr *bbr, uint16_t gain, uint32_t useconds_time, uint64_t bw)
{
	uint64_t divor, res, tim;
	
	if (useconds_time == 0)
		return (0);
	gain = bbr_gain_adjust(bbr, gain);
	divor = (uint64_t)USECS_IN_SECOND * (uint64_t)BBR_UNIT;
	tim = useconds_time;
	res = (tim * bw * gain) / divor;
	if (res == 0)
		res = 1;
	return ((uint32_t)res);
}