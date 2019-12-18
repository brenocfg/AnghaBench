#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vint64 ;
typedef  int /*<<< orphan*/  u_int32 ;
struct TYPE_4__ {scalar_t__ hi; } ;
typedef  TYPE_1__ ntpcal_split ;
typedef  scalar_t__ int32 ;

/* Variables and functions */
 scalar_t__ DAY_NTP_STARTS ; 
 TYPE_1__ ntpcal_daysplit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ntpcal_ntp_to_ntp (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__ ntpcal_split_eradays (scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int32
ntp_to_year(
	u_int32 ntp)
{
	vint64	     t;
	ntpcal_split s;

	t = ntpcal_ntp_to_ntp(ntp, NULL);
	s = ntpcal_daysplit(&t);
	s = ntpcal_split_eradays(s.hi + DAY_NTP_STARTS - 1, NULL);
	return s.hi + 1;
}