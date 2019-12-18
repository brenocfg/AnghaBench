#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint16_t ;
typedef  int /*<<< orphan*/  eeval ;
typedef  scalar_t__ caddr_t ;
struct TYPE_5__ {int ad_id; int ad_in_size; int /*<<< orphan*/  ad_name; int /*<<< orphan*/ * ad_out_data; scalar_t__ ad_out_size; scalar_t__ ad_in_data; } ;
struct TYPE_4__ {void* ee_data; void* ee_off; } ;
typedef  TYPE_1__ HAL_DIAG_EEVAL ;

/* Variables and functions */
 int ATH_DIAG_IN ; 
 int HAL_DIAG_EEWRITE ; 
 int /*<<< orphan*/  SIOCGATHDIAG ; 
 TYPE_2__ atd ; 
 int /*<<< orphan*/  err (int,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  s ; 

__attribute__((used)) static void
eewrite(uint16_t off, uint16_t value)
{
	HAL_DIAG_EEVAL eeval;

	eeval.ee_off = off;
	eeval.ee_data = value;

	atd.ad_id = HAL_DIAG_EEWRITE | ATH_DIAG_IN;
	atd.ad_in_size = sizeof(eeval);
	atd.ad_in_data = (caddr_t) &eeval;
	atd.ad_out_size = 0;
	atd.ad_out_data = NULL;
	if (ioctl(s, SIOCGATHDIAG, &atd) < 0)
		err(1, "ioctl: %s", atd.ad_name);
}