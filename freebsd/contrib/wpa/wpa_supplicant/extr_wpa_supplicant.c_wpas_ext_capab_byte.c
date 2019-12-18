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
typedef  int u8 ;
struct wpa_supplicant {int drv_flags; int /*<<< orphan*/  disable_fils; TYPE_1__* conf; } ;
struct TYPE_2__ {int /*<<< orphan*/  ftm_initiator; int /*<<< orphan*/  ftm_responder; int /*<<< orphan*/  hs20; int /*<<< orphan*/  interworking; int /*<<< orphan*/  disable_btm; int /*<<< orphan*/  coloc_intf_reporting; } ;

/* Variables and functions */
 int WPA_DRIVER_FLAGS_QOS_MAPPING ; 

__attribute__((used)) static void wpas_ext_capab_byte(struct wpa_supplicant *wpa_s, u8 *pos, int idx)
{
	*pos = 0x00;

	switch (idx) {
	case 0: /* Bits 0-7 */
		break;
	case 1: /* Bits 8-15 */
		if (wpa_s->conf->coloc_intf_reporting) {
			/* Bit 13 - Collocated Interference Reporting */
			*pos |= 0x20;
		}
		break;
	case 2: /* Bits 16-23 */
#ifdef CONFIG_WNM
		*pos |= 0x02; /* Bit 17 - WNM-Sleep Mode */
		if (!wpa_s->conf->disable_btm)
			*pos |= 0x08; /* Bit 19 - BSS Transition */
#endif /* CONFIG_WNM */
		break;
	case 3: /* Bits 24-31 */
#ifdef CONFIG_WNM
		*pos |= 0x02; /* Bit 25 - SSID List */
#endif /* CONFIG_WNM */
#ifdef CONFIG_INTERWORKING
		if (wpa_s->conf->interworking)
			*pos |= 0x80; /* Bit 31 - Interworking */
#endif /* CONFIG_INTERWORKING */
		break;
	case 4: /* Bits 32-39 */
#ifdef CONFIG_INTERWORKING
		if (wpa_s->drv_flags & WPA_DRIVER_FLAGS_QOS_MAPPING)
			*pos |= 0x01; /* Bit 32 - QoS Map */
#endif /* CONFIG_INTERWORKING */
		break;
	case 5: /* Bits 40-47 */
#ifdef CONFIG_HS20
		if (wpa_s->conf->hs20)
			*pos |= 0x40; /* Bit 46 - WNM-Notification */
#endif /* CONFIG_HS20 */
#ifdef CONFIG_MBO
		*pos |= 0x40; /* Bit 46 - WNM-Notification */
#endif /* CONFIG_MBO */
		break;
	case 6: /* Bits 48-55 */
		break;
	case 7: /* Bits 56-63 */
		break;
	case 8: /* Bits 64-71 */
		if (wpa_s->conf->ftm_responder)
			*pos |= 0x40; /* Bit 70 - FTM responder */
		if (wpa_s->conf->ftm_initiator)
			*pos |= 0x80; /* Bit 71 - FTM initiator */
		break;
	case 9: /* Bits 72-79 */
#ifdef CONFIG_FILS
		if (!wpa_s->disable_fils)
			*pos |= 0x01;
#endif /* CONFIG_FILS */
		break;
	}
}