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
typedef  scalar_t__ u_int8_t ;

/* Variables and functions */
 int RFCOMM_FRAME_UIH ; 
 scalar_t__ ng_btsocket_rfcomm_fcs2 (scalar_t__*) ; 
 scalar_t__ ng_btsocket_rfcomm_fcs3 (scalar_t__*) ; 

__attribute__((used)) static int
ng_btsocket_rfcomm_check_fcs(u_int8_t *data, int type, u_int8_t fcs)
{
	if (type != RFCOMM_FRAME_UIH)
		return (ng_btsocket_rfcomm_fcs3(data) != fcs);

	return (ng_btsocket_rfcomm_fcs2(data) != fcs);
}