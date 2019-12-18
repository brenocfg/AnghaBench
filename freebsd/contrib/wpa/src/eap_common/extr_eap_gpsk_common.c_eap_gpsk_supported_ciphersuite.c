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
 int EAP_GPSK_CIPHER_AES ; 
 int EAP_GPSK_CIPHER_SHA256 ; 
 int EAP_GPSK_VENDOR_IETF ; 

int eap_gpsk_supported_ciphersuite(int vendor, int specifier)
{
	if (vendor == EAP_GPSK_VENDOR_IETF &&
	    specifier == EAP_GPSK_CIPHER_AES)
		return 1;
#ifdef EAP_GPSK_SHA256
	if (vendor == EAP_GPSK_VENDOR_IETF &&
	    specifier == EAP_GPSK_CIPHER_SHA256)
		return 1;
#endif /* EAP_GPSK_SHA256 */
	return 0;
}