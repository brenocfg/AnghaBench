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
struct hws_qsi_info_block {unsigned long cpu_speed; } ;
typedef  int /*<<< orphan*/  si ;

/* Variables and functions */
 int /*<<< orphan*/  ECAG_CPU_ATTRIBUTE ; 
 unsigned long __ecag (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned long cf_diag_cpu_speed ; 
 scalar_t__ cpum_sf_avail () ; 
 int /*<<< orphan*/  memset (struct hws_qsi_info_block*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  qsi (struct hws_qsi_info_block*) ; 
 scalar_t__ test_facility (int) ; 

__attribute__((used)) static void cf_diag_get_cpu_speed(void)
{
	if (cpum_sf_avail()) {			/* Sampling facility first */
		struct hws_qsi_info_block si;

		memset(&si, 0, sizeof(si));
		if (!qsi(&si)) {
			cf_diag_cpu_speed = si.cpu_speed;
			return;
		}
	}

	if (test_facility(34)) {		/* CPU speed extract static part */
		unsigned long mhz = __ecag(ECAG_CPU_ATTRIBUTE, 0);

		if (mhz != -1UL)
			cf_diag_cpu_speed = mhz & 0xffffffff;
	}
}