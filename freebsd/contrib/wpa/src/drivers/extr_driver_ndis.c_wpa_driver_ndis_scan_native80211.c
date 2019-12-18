#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct wpa_driver_scan_params {int dummy; } ;
struct wpa_driver_ndis_data {int /*<<< orphan*/  ctx; } ;
typedef  int /*<<< orphan*/  req ;
struct TYPE_3__ {int /*<<< orphan*/  dot11ScanType; struct TYPE_3__* dot11BSSID; int /*<<< orphan*/  dot11BSSType; } ;
typedef  TYPE_1__ DOT11_SCAN_REQUEST_V2 ;

/* Variables and functions */
 int ETH_ALEN ; 
 int /*<<< orphan*/  OID_DOT11_SCAN_REQUEST ; 
 int /*<<< orphan*/  dot11_BSS_type_any ; 
 int /*<<< orphan*/  dot11_scan_type_auto ; 
 int /*<<< orphan*/  eloop_cancel_timeout (int /*<<< orphan*/ ,struct wpa_driver_ndis_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eloop_register_timeout (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct wpa_driver_ndis_data*,int /*<<< orphan*/ ) ; 
 int ndis_set_oid (struct wpa_driver_ndis_data*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  os_memset (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  wpa_driver_ndis_scan_timeout ; 

__attribute__((used)) static int wpa_driver_ndis_scan_native80211(
	struct wpa_driver_ndis_data *drv,
	struct wpa_driver_scan_params *params)
{
	DOT11_SCAN_REQUEST_V2 req;
	int res;

	os_memset(&req, 0, sizeof(req));
	req.dot11BSSType = dot11_BSS_type_any;
	os_memset(req.dot11BSSID, 0xff, ETH_ALEN);
	req.dot11ScanType = dot11_scan_type_auto;
	res = ndis_set_oid(drv, OID_DOT11_SCAN_REQUEST, (char *) &req,
			   sizeof(req));
	eloop_cancel_timeout(wpa_driver_ndis_scan_timeout, drv, drv->ctx);
	eloop_register_timeout(7, 0, wpa_driver_ndis_scan_timeout, drv,
			       drv->ctx);
	return res;
}