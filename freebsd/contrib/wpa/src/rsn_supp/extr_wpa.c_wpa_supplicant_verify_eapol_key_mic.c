#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  kck_len; int /*<<< orphan*/  kck; } ;
typedef  TYPE_2__ u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct wpa_eapol_key {struct wpa_eapol_key* replay_counter; int /*<<< orphan*/  kck_len; int /*<<< orphan*/  kck; } ;
struct wpa_sm {int ptk_set; int renew_snonce; int rx_replay_counter_set; TYPE_2__* rx_replay_counter; TYPE_1__* ctx; int /*<<< orphan*/  key_mgmt; TYPE_2__ ptk; struct wpa_eapol_key tptk; scalar_t__ tptk_set; int /*<<< orphan*/  pmk_len; } ;
struct TYPE_8__ {int /*<<< orphan*/  msg_ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/  MSG_WARNING ; 
 int WPA_EAPOL_KEY_MIC_MAX_LEN ; 
 int WPA_REPLAY_COUNTER_LEN ; 
 scalar_t__ os_memcmp_const (TYPE_2__*,struct wpa_eapol_key*,size_t) ; 
 int /*<<< orphan*/  os_memcpy (TYPE_2__*,struct wpa_eapol_key*,int) ; 
 int /*<<< orphan*/  os_memset (struct wpa_eapol_key*,int /*<<< orphan*/ ,size_t) ; 
 scalar_t__ wpa_eapol_key_mic (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__ const*,size_t,TYPE_2__*) ; 
 size_t wpa_mic_len (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int wpa_supplicant_verify_eapol_key_mic(struct wpa_sm *sm,
					       struct wpa_eapol_key *key,
					       u16 ver,
					       const u8 *buf, size_t len)
{
	u8 mic[WPA_EAPOL_KEY_MIC_MAX_LEN];
	int ok = 0;
	size_t mic_len = wpa_mic_len(sm->key_mgmt, sm->pmk_len);

	os_memcpy(mic, key + 1, mic_len);
	if (sm->tptk_set) {
		os_memset(key + 1, 0, mic_len);
		if (wpa_eapol_key_mic(sm->tptk.kck, sm->tptk.kck_len,
				      sm->key_mgmt,
				      ver, buf, len, (u8 *) (key + 1)) < 0 ||
		    os_memcmp_const(mic, key + 1, mic_len) != 0) {
			wpa_msg(sm->ctx->msg_ctx, MSG_WARNING,
				"WPA: Invalid EAPOL-Key MIC "
				"when using TPTK - ignoring TPTK");
#ifdef TEST_FUZZ
			wpa_printf(MSG_INFO,
				   "TEST: Ignore Key MIC failure for fuzz testing");
			goto continue_fuzz;
#endif /* TEST_FUZZ */
		} else {
#ifdef TEST_FUZZ
		continue_fuzz:
#endif /* TEST_FUZZ */
			ok = 1;
			sm->tptk_set = 0;
			sm->ptk_set = 1;
			os_memcpy(&sm->ptk, &sm->tptk, sizeof(sm->ptk));
			os_memset(&sm->tptk, 0, sizeof(sm->tptk));
			/*
			 * This assures the same TPTK in sm->tptk can never be
			 * copied twice to sm->ptk as the new PTK. In
			 * combination with the installed flag in the wpa_ptk
			 * struct, this assures the same PTK is only installed
			 * once.
			 */
			sm->renew_snonce = 1;
		}
	}

	if (!ok && sm->ptk_set) {
		os_memset(key + 1, 0, mic_len);
		if (wpa_eapol_key_mic(sm->ptk.kck, sm->ptk.kck_len,
				      sm->key_mgmt,
				      ver, buf, len, (u8 *) (key + 1)) < 0 ||
		    os_memcmp_const(mic, key + 1, mic_len) != 0) {
			wpa_msg(sm->ctx->msg_ctx, MSG_WARNING,
				"WPA: Invalid EAPOL-Key MIC - "
				"dropping packet");
#ifdef TEST_FUZZ
			wpa_printf(MSG_INFO,
				   "TEST: Ignore Key MIC failure for fuzz testing");
			goto continue_fuzz2;
#endif /* TEST_FUZZ */
			return -1;
		}
#ifdef TEST_FUZZ
	continue_fuzz2:
#endif /* TEST_FUZZ */
		ok = 1;
	}

	if (!ok) {
		wpa_msg(sm->ctx->msg_ctx, MSG_WARNING,
			"WPA: Could not verify EAPOL-Key MIC - "
			"dropping packet");
		return -1;
	}

	os_memcpy(sm->rx_replay_counter, key->replay_counter,
		  WPA_REPLAY_COUNTER_LEN);
	sm->rx_replay_counter_set = 1;
	return 0;
}