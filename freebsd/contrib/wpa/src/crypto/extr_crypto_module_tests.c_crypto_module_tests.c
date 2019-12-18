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
 int /*<<< orphan*/  MSG_INFO ; 
 scalar_t__ test_cbc () ; 
 scalar_t__ test_eax () ; 
 scalar_t__ test_ecb () ; 
 scalar_t__ test_extract_expand_hkdf () ; 
 scalar_t__ test_fips186_2_prf () ; 
 scalar_t__ test_key_wrap () ; 
 scalar_t__ test_md5 () ; 
 scalar_t__ test_ms_funcs () ; 
 scalar_t__ test_omac1 () ; 
 scalar_t__ test_sha1 () ; 
 scalar_t__ test_sha256 () ; 
 scalar_t__ test_sha384 () ; 
 scalar_t__ test_siv () ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

int crypto_module_tests(void)
{
	int ret = 0;

	wpa_printf(MSG_INFO, "crypto module tests");
	if (test_siv() ||
	    test_omac1() ||
	    test_eax() ||
	    test_cbc() ||
	    test_ecb() ||
	    test_key_wrap() ||
	    test_md5() ||
	    test_sha1() ||
	    test_sha256() ||
	    test_sha384() ||
	    test_fips186_2_prf() ||
	    test_extract_expand_hkdf() ||
	    test_ms_funcs())
		ret = -1;

	return ret;
}