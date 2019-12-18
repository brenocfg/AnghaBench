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
typedef  int isc_uint32_t ;
typedef  scalar_t__ isc_uint16_t ;
typedef  scalar_t__ isc_result_t ;

/* Variables and functions */
 scalar_t__ ISC_R_RANGE ; 
 scalar_t__ ISC_R_SUCCESS ; 
 scalar_t__ isc_parse_uint32 (int*,char const*,int) ; 

isc_result_t
isc_parse_uint16(isc_uint16_t *uip, const char *string, int base) {
	isc_uint32_t val;
	isc_result_t result;
	result = isc_parse_uint32(&val, string, base);
	if (result != ISC_R_SUCCESS)
		return (result);
	if (val > 0xFFFF)
		return (ISC_R_RANGE);
	*uip = (isc_uint16_t) val;
	return (ISC_R_SUCCESS);
}