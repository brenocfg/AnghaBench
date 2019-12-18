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
struct wpa_scan_results {size_t num; int ie_len; int beacon_ie_len; struct wpa_scan_results** res; } ;
typedef  struct wpa_scan_results u8 ;
struct wpa_scan_res {size_t num; int ie_len; int beacon_ie_len; struct wpa_scan_res** res; } ;
struct wpa_driver_privsep_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 int /*<<< orphan*/  PRIVSEP_CMD_GET_SCAN_RESULTS ; 
 struct wpa_scan_results** os_calloc (int,int) ; 
 int /*<<< orphan*/  os_free (struct wpa_scan_results*) ; 
 struct wpa_scan_results* os_malloc (size_t) ; 
 int /*<<< orphan*/  os_memcpy (int*,struct wpa_scan_results*,int) ; 
 struct wpa_scan_results* os_memdup (struct wpa_scan_results*,int) ; 
 struct wpa_scan_results* os_zalloc (int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int,...) ; 
 int wpa_priv_cmd (struct wpa_driver_privsep_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct wpa_scan_results*,size_t*) ; 

__attribute__((used)) static struct wpa_scan_results *
wpa_driver_privsep_get_scan_results2(void *priv)
{
	struct wpa_driver_privsep_data *drv = priv;
	int res, num;
	u8 *buf, *pos, *end;
	size_t reply_len = 60000;
	struct wpa_scan_results *results;
	struct wpa_scan_res *r;

	buf = os_malloc(reply_len);
	if (buf == NULL)
		return NULL;
	res = wpa_priv_cmd(drv, PRIVSEP_CMD_GET_SCAN_RESULTS,
			   NULL, 0, buf, &reply_len);
	if (res < 0) {
		os_free(buf);
		return NULL;
	}

	wpa_printf(MSG_DEBUG, "privsep: Received %lu bytes of scan results",
		   (unsigned long) reply_len);
	if (reply_len < sizeof(int)) {
		wpa_printf(MSG_DEBUG, "privsep: Invalid scan result len %lu",
			   (unsigned long) reply_len);
		os_free(buf);
		return NULL;
	}

	pos = buf;
	end = buf + reply_len;
	os_memcpy(&num, pos, sizeof(int));
	if (num < 0 || num > 1000) {
		os_free(buf);
		return NULL;
	}
	pos += sizeof(int);

	results = os_zalloc(sizeof(*results));
	if (results == NULL) {
		os_free(buf);
		return NULL;
	}

	results->res = os_calloc(num, sizeof(struct wpa_scan_res *));
	if (results->res == NULL) {
		os_free(results);
		os_free(buf);
		return NULL;
	}

	while (results->num < (size_t) num && end - pos > (int) sizeof(int)) {
		int len;
		os_memcpy(&len, pos, sizeof(int));
		pos += sizeof(int);
		if (len < 0 || len > 10000 || len > end - pos)
			break;

		r = os_memdup(pos, len);
		if (r == NULL)
			break;
		pos += len;
		if (sizeof(*r) + r->ie_len + r->beacon_ie_len > (size_t) len) {
			wpa_printf(MSG_ERROR,
				   "privsep: Invalid scan result len (%d + %d + %d > %d)",
				   (int) sizeof(*r), (int) r->ie_len,
				   (int) r->beacon_ie_len, len);
			os_free(r);
			break;
		}

		results->res[results->num++] = r;
	}

	os_free(buf);
	return results;
}