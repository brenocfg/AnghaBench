#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct wps_er_ap {TYPE_2__* wps; TYPE_1__* er; } ;
struct wps_config {int registrar; int /*<<< orphan*/  wps; } ;
struct wpabuf {int dummy; } ;
typedef  int /*<<< orphan*/  cfg ;
struct TYPE_4__ {struct wps_er_ap* ap_settings_cb_ctx; int /*<<< orphan*/  ap_settings_cb; } ;
struct TYPE_3__ {int /*<<< orphan*/  wps; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  os_memset (struct wps_config*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wps_er_ap_process (struct wps_er_ap*,struct wpabuf*) ; 
 int /*<<< orphan*/  wps_er_ap_settings_cb ; 
 TYPE_2__* wps_init (struct wps_config*) ; 

__attribute__((used)) static void wps_er_ap_learn_m1(struct wps_er_ap *ap, struct wpabuf *m1)
{
	struct wps_config cfg;

	if (ap->wps) {
		wpa_printf(MSG_DEBUG, "WPS ER: Protocol run already in "
			   "progress with this AP");
		return;
	}

	os_memset(&cfg, 0, sizeof(cfg));
	cfg.wps = ap->er->wps;
	cfg.registrar = 1;
	ap->wps = wps_init(&cfg);
	if (ap->wps == NULL)
		return;
	ap->wps->ap_settings_cb = wps_er_ap_settings_cb;
	ap->wps->ap_settings_cb_ctx = ap;

	wps_er_ap_process(ap, m1);
}