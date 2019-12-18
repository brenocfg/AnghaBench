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
typedef  scalar_t__ u8 ;
struct wpa_sm {TYPE_1__* ctx; int /*<<< orphan*/  group_cipher; int /*<<< orphan*/  wpa_rsc_relaxation; } ;
struct TYPE_2__ {int /*<<< orphan*/  msg_ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_WARNING ; 
 int wpa_cipher_rsc_len (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,scalar_t__ const,scalar_t__ const,scalar_t__ const,scalar_t__ const,scalar_t__ const,scalar_t__ const,scalar_t__ const,scalar_t__ const) ; 

__attribute__((used)) static int wpa_supplicant_rsc_relaxation(const struct wpa_sm *sm,
					 const u8 *rsc)
{
	int rsclen;

	if (!sm->wpa_rsc_relaxation)
		return 0;

	rsclen = wpa_cipher_rsc_len(sm->group_cipher);

	/*
	 * Try to detect RSC (endian) corruption issue where the AP sends
	 * the RSC bytes in EAPOL-Key message in the wrong order, both if
	 * it's actually a 6-byte field (as it should be) and if it treats
	 * it as an 8-byte field.
	 * An AP model known to have this bug is the Sapido RB-1632.
	 */
	if (rsclen == 6 && ((rsc[5] && !rsc[0]) || rsc[6] || rsc[7])) {
		wpa_msg(sm->ctx->msg_ctx, MSG_WARNING,
			"RSC %02x%02x%02x%02x%02x%02x%02x%02x is likely bogus, using 0",
			rsc[0], rsc[1], rsc[2], rsc[3],
			rsc[4], rsc[5], rsc[6], rsc[7]);

		return 1;
	}

	return 0;
}