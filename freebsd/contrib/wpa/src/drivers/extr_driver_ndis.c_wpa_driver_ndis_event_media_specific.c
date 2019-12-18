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
struct wpa_driver_ndis_data {int dummy; } ;
typedef  int /*<<< orphan*/  status ;
struct TYPE_2__ {int StatusType; } ;
typedef  TYPE_1__ NDIS_802_11_STATUS_INDICATION ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
#define  Ndis802_11StatusType_Authentication 129 
#define  Ndis802_11StatusType_PMKID_CandidateList 128 
 int /*<<< orphan*/  wpa_driver_ndis_event_auth (struct wpa_driver_ndis_data*,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  wpa_driver_ndis_event_pmkid (struct wpa_driver_ndis_data*,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int) ; 

void wpa_driver_ndis_event_media_specific(struct wpa_driver_ndis_data *drv,
					  const u8 *data, size_t data_len)
{
	NDIS_802_11_STATUS_INDICATION *status;

	if (data == NULL || data_len < sizeof(*status))
		return;

	wpa_hexdump(MSG_DEBUG, "NDIS: Media Specific Indication",
		    data, data_len);

	status = (NDIS_802_11_STATUS_INDICATION *) data;
	data += sizeof(status);
	data_len -= sizeof(status);

	switch (status->StatusType) {
	case Ndis802_11StatusType_Authentication:
		wpa_driver_ndis_event_auth(drv, data, data_len);
		break;
	case Ndis802_11StatusType_PMKID_CandidateList:
		wpa_driver_ndis_event_pmkid(drv, data, data_len);
		break;
	default:
		wpa_printf(MSG_DEBUG, "NDIS: Unknown StatusType %d",
			   (int) status->StatusType);
		break;
	}
}