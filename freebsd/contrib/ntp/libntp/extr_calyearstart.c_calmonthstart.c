#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vint64 ;
typedef  int u_int32 ;
typedef  int /*<<< orphan*/  time_t ;
struct TYPE_3__ {int hi; } ;
typedef  TYPE_1__ ntpcal_split ;

/* Variables and functions */
 int DAY_NTP_STARTS ; 
 int SECSPERDAY ; 
 TYPE_1__ ntpcal_daysplit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ntpcal_ntp_to_ntp (int,int /*<<< orphan*/  const*) ; 
 int ntpcal_rd_to_mstart (int) ; 

u_int32
calmonthstart(u_int32 ntptime, const time_t *pivot)
{
	u_int32      ndays; /* elapsed days since NTP starts */
	vint64       vlong;
	ntpcal_split split;

	vlong = ntpcal_ntp_to_ntp(ntptime, pivot);
	split = ntpcal_daysplit(&vlong);
	ndays = ntpcal_rd_to_mstart(split.hi + DAY_NTP_STARTS)
	      - DAY_NTP_STARTS;

	return (u_int32)(ndays * SECSPERDAY);
}