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
typedef  int /*<<< orphan*/  wpa_s ;
typedef  int /*<<< orphan*/  u8 ;
struct wpa_supplicant {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_ERROR ; 
 int /*<<< orphan*/  os_memset (struct wpa_supplicant*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ wpa_blacklist_add (struct wpa_supplicant*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpa_blacklist_clear (struct wpa_supplicant*) ; 
 scalar_t__ wpa_blacklist_del (struct wpa_supplicant*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * wpa_blacklist_get (struct wpa_supplicant*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int wpas_blacklist_module_tests(void)
{
	struct wpa_supplicant wpa_s;
	int ret = -1;

	os_memset(&wpa_s, 0, sizeof(wpa_s));

	wpa_blacklist_clear(&wpa_s);

	if (wpa_blacklist_get(NULL, NULL) != NULL ||
	    wpa_blacklist_get(NULL, (u8 *) "123456") != NULL ||
	    wpa_blacklist_get(&wpa_s, NULL) != NULL ||
	    wpa_blacklist_get(&wpa_s, (u8 *) "123456") != NULL)
		goto fail;

	if (wpa_blacklist_add(NULL, NULL) == 0 ||
	    wpa_blacklist_add(NULL, (u8 *) "123456") == 0 ||
	    wpa_blacklist_add(&wpa_s, NULL) == 0)
		goto fail;

	if (wpa_blacklist_del(NULL, NULL) == 0 ||
	    wpa_blacklist_del(NULL, (u8 *) "123456") == 0 ||
	    wpa_blacklist_del(&wpa_s, NULL) == 0 ||
	    wpa_blacklist_del(&wpa_s, (u8 *) "123456") == 0)
		goto fail;

	if (wpa_blacklist_add(&wpa_s, (u8 *) "111111") < 0 ||
	    wpa_blacklist_add(&wpa_s, (u8 *) "111111") < 0 ||
	    wpa_blacklist_add(&wpa_s, (u8 *) "222222") < 0 ||
	    wpa_blacklist_add(&wpa_s, (u8 *) "333333") < 0 ||
	    wpa_blacklist_add(&wpa_s, (u8 *) "444444") < 0 ||
	    wpa_blacklist_del(&wpa_s, (u8 *) "333333") < 0 ||
	    wpa_blacklist_del(&wpa_s, (u8 *) "xxxxxx") == 0 ||
	    wpa_blacklist_get(&wpa_s, (u8 *) "xxxxxx") != NULL ||
	    wpa_blacklist_get(&wpa_s, (u8 *) "111111") == NULL ||
	    wpa_blacklist_get(&wpa_s, (u8 *) "222222") == NULL ||
	    wpa_blacklist_get(&wpa_s, (u8 *) "444444") == NULL ||
	    wpa_blacklist_del(&wpa_s, (u8 *) "111111") < 0 ||
	    wpa_blacklist_del(&wpa_s, (u8 *) "222222") < 0 ||
	    wpa_blacklist_del(&wpa_s, (u8 *) "444444") < 0 ||
	    wpa_blacklist_add(&wpa_s, (u8 *) "111111") < 0 ||
	    wpa_blacklist_add(&wpa_s, (u8 *) "222222") < 0 ||
	    wpa_blacklist_add(&wpa_s, (u8 *) "333333") < 0)
		goto fail;

	ret = 0;
fail:
	wpa_blacklist_clear(&wpa_s);

	if (ret)
		wpa_printf(MSG_ERROR, "blacklist module test failure");

	return ret;
}