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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {size_t kck_len; size_t kek_len; int /*<<< orphan*/  kek; int /*<<< orphan*/  kck; } ;
struct wpa_sm {int ptk_set; TYPE_1__ ptk; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 size_t WPA_KCK_MAX_LEN ; 
 size_t WPA_KEK_MAX_LEN ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

void wpa_sm_set_ptk_kck_kek(struct wpa_sm *sm,
			    const u8 *ptk_kck, size_t ptk_kck_len,
			    const u8 *ptk_kek, size_t ptk_kek_len)
{
	if (ptk_kck && ptk_kck_len <= WPA_KCK_MAX_LEN) {
		os_memcpy(sm->ptk.kck, ptk_kck, ptk_kck_len);
		sm->ptk.kck_len = ptk_kck_len;
		wpa_printf(MSG_DEBUG, "Updated PTK KCK");
	}
	if (ptk_kek && ptk_kek_len <= WPA_KEK_MAX_LEN) {
		os_memcpy(sm->ptk.kek, ptk_kek, ptk_kek_len);
		sm->ptk.kek_len = ptk_kek_len;
		wpa_printf(MSG_DEBUG, "Updated PTK KEK");
	}
	sm->ptk_set = 1;
}