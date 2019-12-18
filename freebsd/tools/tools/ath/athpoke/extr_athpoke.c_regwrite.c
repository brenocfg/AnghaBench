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
typedef  void* uint32_t ;
struct ath_diag {int ad_in_size; int ad_id; int /*<<< orphan*/  ad_name; scalar_t__ ad_in_data; } ;
typedef  int /*<<< orphan*/  rw ;
typedef  scalar_t__ caddr_t ;
struct TYPE_2__ {void* value; void* addr; } ;
typedef  TYPE_1__ HAL_REGWRITE ;

/* Variables and functions */
 int ATH_DIAG_IN ; 
 int HAL_DIAG_SETREGS ; 
 int /*<<< orphan*/  SIOCGATHDIAG ; 
 int /*<<< orphan*/  err (int,int /*<<< orphan*/ ) ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,struct ath_diag*) ; 

__attribute__((used)) static void
regwrite(int s, struct ath_diag *atd, uint32_t r, uint32_t v)
{
	HAL_REGWRITE rw;

	rw.addr = r;
	rw.value = v;
	atd->ad_in_data = (caddr_t) &rw;
	atd->ad_in_size = sizeof(rw);
	atd->ad_id = HAL_DIAG_SETREGS | ATH_DIAG_IN;
	if (ioctl(s, SIOCGATHDIAG, atd) < 0)
		err(1, atd->ad_name);
}