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
typedef  scalar_t__ u8 ;

/* Variables and functions */
 scalar_t__ EAP_TYPE_EKE ; 
 scalar_t__ EAP_TYPE_PWD ; 

int eap_teap_allowed_anon_prov_phase2_method(u8 type)
{
	/* RFC 7170, Section 3.8.3: MUST provide mutual authentication,
	 * provide key generation, and be resistant to dictionary attack.
	 * Section 3.8 also mentions requirement for using EMSK Compound MAC. */
	return type == EAP_TYPE_PWD || type == EAP_TYPE_EKE;
}