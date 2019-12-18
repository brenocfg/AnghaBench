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
typedef  int /*<<< orphan*/  u8 ;
struct wpa_supplicant {int /*<<< orphan*/ * dpp_pkex; int /*<<< orphan*/  dpp; } ;
struct dpp_bootstrap_info {int dummy; } ;

/* Variables and functions */
 struct dpp_bootstrap_info* dpp_pkex_finish (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,unsigned int) ; 

__attribute__((used)) static struct dpp_bootstrap_info *
wpas_dpp_pkex_finish(struct wpa_supplicant *wpa_s, const u8 *peer,
		     unsigned int freq)
{
	struct dpp_bootstrap_info *bi;

	bi = dpp_pkex_finish(wpa_s->dpp, wpa_s->dpp_pkex, peer, freq);
	if (!bi)
		return NULL;
	wpa_s->dpp_pkex = NULL;
	return bi;
}