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
struct wpa_ie_data {int dummy; } ;
struct rsn_ie_parse_test_data {scalar_t__ result; int /*<<< orphan*/  len; scalar_t__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_ERROR ; 
 int /*<<< orphan*/  MSG_INFO ; 
 struct rsn_ie_parse_test_data* rsn_parse_tests ; 
 scalar_t__ wpa_parse_wpa_ie_rsn (scalar_t__,int /*<<< orphan*/ ,struct wpa_ie_data*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int rsn_ie_parse_tests(void)
{
	int i, ret = 0;

	wpa_printf(MSG_INFO, "rsn_ie_parse tests");

	for (i = 0; rsn_parse_tests[i].data; i++) {
		const struct rsn_ie_parse_test_data *test;
		struct wpa_ie_data data;

		test = &rsn_parse_tests[i];
		if (wpa_parse_wpa_ie_rsn(test->data, test->len, &data) !=
		    test->result) {
			wpa_printf(MSG_ERROR, "rsn_ie_parse test %d failed", i);
			ret = -1;
		}
	}

	return ret;
}