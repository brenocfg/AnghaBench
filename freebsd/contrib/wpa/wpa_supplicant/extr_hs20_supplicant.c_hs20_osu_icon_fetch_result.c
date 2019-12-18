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
struct wpa_supplicant {size_t osu_prov_count; scalar_t__ osu_icon_id; struct osu_provider* osu_prov; int /*<<< orphan*/  osu_icon_fetch_start; } ;
struct osu_provider {size_t icon_count; struct osu_icon* icon; } ;
struct osu_icon {int failed; scalar_t__ id; } ;
struct os_reltime {int sec; int usec; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  os_get_reltime (struct os_reltime*) ; 
 int /*<<< orphan*/  os_reltime_sub (struct os_reltime*,int /*<<< orphan*/ *,struct os_reltime*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int,int) ; 

__attribute__((used)) static void hs20_osu_icon_fetch_result(struct wpa_supplicant *wpa_s, int res)
{
	size_t i, j;
	struct os_reltime now, tmp;
	int dur;

	os_get_reltime(&now);
	os_reltime_sub(&now, &wpa_s->osu_icon_fetch_start, &tmp);
	dur = tmp.sec * 1000 + tmp.usec / 1000;
	wpa_printf(MSG_DEBUG, "HS 2.0: Icon fetch dur=%d ms res=%d",
		   dur, res);

	for (i = 0; i < wpa_s->osu_prov_count; i++) {
		struct osu_provider *osu = &wpa_s->osu_prov[i];
		for (j = 0; j < osu->icon_count; j++) {
			struct osu_icon *icon = &osu->icon[j];
			if (icon->id || icon->failed)
				continue;
			if (res < 0)
				icon->failed = 1;
			else
				icon->id = wpa_s->osu_icon_id;
			return;
		}
	}
}