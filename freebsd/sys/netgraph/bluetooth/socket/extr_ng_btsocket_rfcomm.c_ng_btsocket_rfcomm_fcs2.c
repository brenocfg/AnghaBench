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
 scalar_t__ ng_btsocket_rfcomm_crc (scalar_t__*,int) ; 

__attribute__((used)) static u_int8_t
ng_btsocket_rfcomm_fcs2(u_int8_t *data)
{
	return (0xff - ng_btsocket_rfcomm_crc(data, 2));
}