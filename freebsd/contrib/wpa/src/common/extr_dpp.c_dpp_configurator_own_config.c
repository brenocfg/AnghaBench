#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct wpabuf {int dummy; } ;
struct dpp_authentication {int /*<<< orphan*/ * peer_protocol_key; TYPE_1__* conf; int /*<<< orphan*/ * own_protocol_key; TYPE_2__* curve; } ;
struct TYPE_6__ {char const* name; } ;
struct TYPE_5__ {int /*<<< orphan*/  csign; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_INFO ; 
 struct wpabuf* dpp_build_conf_obj (struct dpp_authentication*,int) ; 
 int /*<<< orphan*/  dpp_copy_csign (struct dpp_authentication*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dpp_copy_netaccesskey (struct dpp_authentication*) ; 
 TYPE_2__* dpp_curves ; 
 int /*<<< orphan*/ * dpp_gen_keypair (TYPE_2__*) ; 
 TYPE_2__* dpp_get_curve_name (char const*) ; 
 int dpp_parse_conf_obj (struct dpp_authentication*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  wpabuf_free (struct wpabuf*) ; 
 int /*<<< orphan*/  wpabuf_head (struct wpabuf*) ; 
 int /*<<< orphan*/  wpabuf_len (struct wpabuf*) ; 

int dpp_configurator_own_config(struct dpp_authentication *auth,
				const char *curve, int ap)
{
	struct wpabuf *conf_obj;
	int ret = -1;

	if (!auth->conf) {
		wpa_printf(MSG_DEBUG, "DPP: No configurator specified");
		return -1;
	}

	if (!curve) {
		auth->curve = &dpp_curves[0];
	} else {
		auth->curve = dpp_get_curve_name(curve);
		if (!auth->curve) {
			wpa_printf(MSG_INFO, "DPP: Unsupported curve: %s",
				   curve);
			return -1;
		}
	}
	wpa_printf(MSG_DEBUG,
		   "DPP: Building own configuration/connector with curve %s",
		   auth->curve->name);

	auth->own_protocol_key = dpp_gen_keypair(auth->curve);
	if (!auth->own_protocol_key)
		return -1;
	dpp_copy_netaccesskey(auth);
	auth->peer_protocol_key = auth->own_protocol_key;
	dpp_copy_csign(auth, auth->conf->csign);

	conf_obj = dpp_build_conf_obj(auth, ap);
	if (!conf_obj)
		goto fail;
	ret = dpp_parse_conf_obj(auth, wpabuf_head(conf_obj),
				 wpabuf_len(conf_obj));
fail:
	wpabuf_free(conf_obj);
	auth->peer_protocol_key = NULL;
	return ret;
}