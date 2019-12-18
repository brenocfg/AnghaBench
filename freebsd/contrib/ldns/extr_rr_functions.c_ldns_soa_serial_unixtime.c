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
typedef  scalar_t__ uint32_t ;
typedef  scalar_t__ int32_t ;

/* Variables and functions */
 scalar_t__ ldns_time (int /*<<< orphan*/ *) ; 

uint32_t ldns_soa_serial_unixtime(uint32_t s, void *data)
{
	int32_t new_s = data ? (int32_t) (intptr_t) data 
			     : (int32_t) ldns_time(NULL);
	return new_s - ((int32_t) s) <= 0 ? s+1 : ((uint32_t) new_s);
}