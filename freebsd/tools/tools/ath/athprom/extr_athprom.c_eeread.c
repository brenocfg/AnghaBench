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
typedef  int /*<<< orphan*/  u_int16_t ;
typedef  int /*<<< orphan*/  off ;
typedef  int /*<<< orphan*/  eedata ;
typedef  void* caddr_t ;
struct TYPE_3__ {int ad_id; int ad_in_size; int ad_out_size; int /*<<< orphan*/  ad_name; void* ad_out_data; void* ad_in_data; } ;

/* Variables and functions */
 int ATH_DIAG_DYN ; 
 int ATH_DIAG_IN ; 
 int HAL_DIAG_EEREAD ; 
 int /*<<< orphan*/  SIOCGATHDIAG ; 
 TYPE_1__ atd ; 
 int /*<<< orphan*/  err (int,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  s ; 

__attribute__((used)) static u_int16_t
eeread(u_int16_t off)
{
	u_int16_t eedata;

	atd.ad_id = HAL_DIAG_EEREAD | ATH_DIAG_IN | ATH_DIAG_DYN;
	atd.ad_in_size = sizeof(off);
	atd.ad_in_data = (caddr_t) &off;
	atd.ad_out_size = sizeof(eedata);
	atd.ad_out_data = (caddr_t) &eedata;
	if (ioctl(s, SIOCGATHDIAG, &atd) < 0)
		err(1, "ioctl: %s", atd.ad_name);
	return eedata;
}