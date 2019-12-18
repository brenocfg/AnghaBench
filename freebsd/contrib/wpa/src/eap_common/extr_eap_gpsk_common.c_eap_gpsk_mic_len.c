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
#define  EAP_GPSK_CIPHER_AES 129 
#define  EAP_GPSK_CIPHER_SHA256 128 
 int EAP_GPSK_VENDOR_IETF ; 

size_t eap_gpsk_mic_len(int vendor, int specifier)
{
	if (vendor != EAP_GPSK_VENDOR_IETF)
		return 0;

	switch (specifier) {
	case EAP_GPSK_CIPHER_AES:
		return 16;
#ifdef EAP_GPSK_SHA256
	case EAP_GPSK_CIPHER_SHA256:
		return 32;
#endif /* EAP_GPSK_SHA256 */
	default:
		return 0;
	}
}