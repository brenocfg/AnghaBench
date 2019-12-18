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
typedef  int uint8_t ;
typedef  int target_id_t ;
typedef  int lun_id_t ;

/* Variables and functions */

__attribute__((used)) static void
vtscsi_get_request_lun(uint8_t lun[], target_id_t *target_id, lun_id_t *lun_id)
{

	*target_id = lun[1];
	*lun_id = (lun[2] << 8) | lun[3];
}