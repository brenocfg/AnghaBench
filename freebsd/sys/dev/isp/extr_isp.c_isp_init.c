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
typedef  int /*<<< orphan*/  ispsoftc_t ;

/* Variables and functions */
 scalar_t__ IS_24XX (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_FC (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  isp_fibre_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  isp_fibre_init_2400 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  isp_scsi_init (int /*<<< orphan*/ *) ; 

void
isp_init(ispsoftc_t *isp)
{
	if (IS_FC(isp)) {
		if (IS_24XX(isp)) {
			isp_fibre_init_2400(isp);
		} else {
			isp_fibre_init(isp);
		}
	} else {
		isp_scsi_init(isp);
	}
}