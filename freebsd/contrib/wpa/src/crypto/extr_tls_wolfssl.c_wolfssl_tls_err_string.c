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
#define  ASN_AFTER_DATE_E 129 
#define  ASN_BEFORE_DATE_E 128 

__attribute__((used)) static const char * wolfssl_tls_err_string(int err, const char *err_str)
{
	switch (err) {
	case ASN_BEFORE_DATE_E:
		return "certificate is not yet valid";
	case ASN_AFTER_DATE_E:
		return "certificate has expired";
	default:
		return err_str;
	}
}