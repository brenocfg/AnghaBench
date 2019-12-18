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
typedef  int uint64_t ;
typedef  int uint32_t ;

/* Variables and functions */
 int RPL_LUNDATA_ATYP_EXTLUN ; 
 scalar_t__ RPL_LUNDATA_ATYP_FLAT ; 
 scalar_t__ RPL_LUNDATA_ATYP_PERIPH ; 

uint64_t
ctl_encode_lun(uint32_t decoded)
{
	uint64_t l = decoded;

	if (l <= 0xff)
		return (((uint64_t)RPL_LUNDATA_ATYP_PERIPH << 56) | (l << 48));
	if (l <= 0x3fff)
		return (((uint64_t)RPL_LUNDATA_ATYP_FLAT << 56) | (l << 48));
	if (l <= 0xffffff)
		return (((uint64_t)(RPL_LUNDATA_ATYP_EXTLUN | 0x12) << 56) |
		    (l << 32));
	return ((((uint64_t)RPL_LUNDATA_ATYP_EXTLUN | 0x22) << 56) | (l << 16));
}