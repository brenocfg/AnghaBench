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
 scalar_t__ base64_tests () ; 
 scalar_t__ bitfield_tests () ; 
 scalar_t__ common_tests () ; 
 scalar_t__ const_time_tests () ; 
 scalar_t__ eloop_tests () ; 
 scalar_t__ ext_password_tests () ; 
 scalar_t__ int_array_tests () ; 
 scalar_t__ ip_addr_tests () ; 
 scalar_t__ json_tests () ; 
 scalar_t__ os_tests () ; 
 scalar_t__ printf_encode_decode_tests () ; 
 scalar_t__ trace_tests () ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ wpabuf_tests () ; 

int utils_module_tests(void)
{
	int ret = 0;

	wpa_printf(MSG_INFO, "utils module tests");

	if (printf_encode_decode_tests() < 0 ||
	    ext_password_tests() < 0 ||
	    trace_tests() < 0 ||
	    bitfield_tests() < 0 ||
	    base64_tests() < 0 ||
	    common_tests() < 0 ||
	    os_tests() < 0 ||
	    wpabuf_tests() < 0 ||
	    ip_addr_tests() < 0 ||
	    eloop_tests() < 0 ||
	    json_tests() < 0 ||
	    const_time_tests() < 0 ||
	    int_array_tests() < 0)
		ret = -1;

	return ret;
}