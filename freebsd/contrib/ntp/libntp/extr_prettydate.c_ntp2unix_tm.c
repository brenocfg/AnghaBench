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
typedef  int /*<<< orphan*/  vint64 ;
typedef  int /*<<< orphan*/  u_int32 ;
struct tm {int dummy; } ;

/* Variables and functions */
 struct tm* get_struct_tm (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ntpcal_ntp_to_time (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

struct tm *
ntp2unix_tm(
	u_int32 ntp, int local
	)
{
	vint64 vl;
	vl = ntpcal_ntp_to_time(ntp, NULL);
	return get_struct_tm(&vl, local);
}