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
struct wpabuf {int dummy; } ;
struct dpp_authentication {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_MSGDUMP ; 
 struct wpabuf* dpp_build_conf_req_attr (struct dpp_authentication*,char const*) ; 
 int /*<<< orphan*/  dpp_write_adv_proto (struct wpabuf*) ; 
 int /*<<< orphan*/  dpp_write_gas_query (struct wpabuf*,struct wpabuf*) ; 
 struct wpabuf* gas_build_initial_req (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  wpa_hexdump_buf (int /*<<< orphan*/ ,char*,struct wpabuf*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wpabuf_free (struct wpabuf*) ; 
 scalar_t__ wpabuf_len (struct wpabuf*) ; 

struct wpabuf * dpp_build_conf_req(struct dpp_authentication *auth,
				   const char *json)
{
	struct wpabuf *buf, *conf_req;

	conf_req = dpp_build_conf_req_attr(auth, json);
	if (!conf_req) {
		wpa_printf(MSG_DEBUG,
			   "DPP: No configuration request data available");
		return NULL;
	}

	buf = gas_build_initial_req(0, 10 + 2 + wpabuf_len(conf_req));
	if (!buf) {
		wpabuf_free(conf_req);
		return NULL;
	}

	dpp_write_adv_proto(buf);
	dpp_write_gas_query(buf, conf_req);
	wpabuf_free(conf_req);
	wpa_hexdump_buf(MSG_MSGDUMP, "DPP: GAS Config Request", buf);

	return buf;
}