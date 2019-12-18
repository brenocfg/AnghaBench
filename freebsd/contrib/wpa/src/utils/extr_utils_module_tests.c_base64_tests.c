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
 int /*<<< orphan*/  MSG_ERROR ; 
 int /*<<< orphan*/  MSG_INFO ; 
 unsigned char* base64_decode (unsigned char const*,int,size_t*) ; 
 unsigned char* base64_encode (unsigned char const*,int,size_t*) ; 
 int /*<<< orphan*/  os_free (unsigned char*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int base64_tests(void)
{
	int errors = 0;
	unsigned char *res;
	size_t res_len;

	wpa_printf(MSG_INFO, "base64 tests");

	res = base64_encode((const unsigned char *) "", ~0, &res_len);
	if (res) {
		errors++;
		os_free(res);
	}

	res = base64_encode((const unsigned char *) "=", 1, &res_len);
	if (!res || res_len != 5 || res[0] != 'P' || res[1] != 'Q' ||
	    res[2] != '=' || res[3] != '=' || res[4] != '\n')
		errors++;
	os_free(res);

	res = base64_encode((const unsigned char *) "=", 1, NULL);
	if (!res || res[0] != 'P' || res[1] != 'Q' ||
	    res[2] != '=' || res[3] != '=' || res[4] != '\n')
		errors++;
	os_free(res);

	res = base64_decode((const unsigned char *) "", 0, &res_len);
	if (res) {
		errors++;
		os_free(res);
	}

	res = base64_decode((const unsigned char *) "a", 1, &res_len);
	if (res) {
		errors++;
		os_free(res);
	}

	res = base64_decode((const unsigned char *) "====", 4, &res_len);
	if (res) {
		errors++;
		os_free(res);
	}

	res = base64_decode((const unsigned char *) "PQ==", 4, &res_len);
	if (!res || res_len != 1 || res[0] != '=')
		errors++;
	os_free(res);

	res = base64_decode((const unsigned char *) "P.Q-=!=*", 8, &res_len);
	if (!res || res_len != 1 || res[0] != '=')
		errors++;
	os_free(res);

	if (errors) {
		wpa_printf(MSG_ERROR, "%d base64 test(s) failed", errors);
		return -1;
	}

	return 0;
}