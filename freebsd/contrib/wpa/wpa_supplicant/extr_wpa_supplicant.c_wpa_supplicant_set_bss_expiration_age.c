#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct wpa_supplicant {TYPE_1__* conf; } ;
struct TYPE_2__ {unsigned int bss_expiration_age; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 int /*<<< orphan*/  wpa_msg (struct wpa_supplicant*,int /*<<< orphan*/ ,char*,unsigned int) ; 

int wpa_supplicant_set_bss_expiration_age(struct wpa_supplicant *wpa_s,
					  unsigned int bss_expire_age)
{
	if (bss_expire_age < 10) {
		wpa_msg(wpa_s, MSG_ERROR, "Invalid bss expiration age %u",
			bss_expire_age);
		return -1;
	}
	wpa_msg(wpa_s, MSG_DEBUG, "Setting bss expiration age: %d sec",
		bss_expire_age);
	wpa_s->conf->bss_expiration_age = bss_expire_age;

	return 0;
}