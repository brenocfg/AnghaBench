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
 scalar_t__ EAP_EKE_ENCR_AES128_CBC ; 

__attribute__((used)) static int eap_eke_supp_encr(u8 encr)
{
	return encr == EAP_EKE_ENCR_AES128_CBC;
}