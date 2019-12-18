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

/* Variables and functions */
 int EAP_TYPE_FAST ; 
 int EAP_TYPE_PEAP ; 
 int EAP_TYPE_TEAP ; 
 int EAP_TYPE_TTLS ; 
 int EAP_VENDOR_IETF ; 

__attribute__((used)) static int eap_allowed_phase2_type(int vendor, int type)
{
	if (vendor != EAP_VENDOR_IETF)
		return 0;
	return type != EAP_TYPE_PEAP && type != EAP_TYPE_TTLS &&
		type != EAP_TYPE_FAST && type != EAP_TYPE_TEAP;
}