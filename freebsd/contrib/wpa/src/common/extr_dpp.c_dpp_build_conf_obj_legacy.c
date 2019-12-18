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
struct dpp_configuration {int /*<<< orphan*/  akm; } ;
struct dpp_authentication {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  dpp_akm_str (int /*<<< orphan*/ ) ; 
 struct wpabuf* dpp_build_conf_start (struct dpp_authentication*,struct dpp_configuration*,int) ; 
 int /*<<< orphan*/  dpp_build_legacy_cred_params (struct wpabuf*,struct dpp_configuration*) ; 
 int /*<<< orphan*/  wpa_hexdump_ascii_key (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpabuf_head (struct wpabuf*) ; 
 int /*<<< orphan*/  wpabuf_len (struct wpabuf*) ; 
 int /*<<< orphan*/  wpabuf_printf (struct wpabuf*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpabuf_put_str (struct wpabuf*,char*) ; 

__attribute__((used)) static struct wpabuf *
dpp_build_conf_obj_legacy(struct dpp_authentication *auth, int ap,
			  struct dpp_configuration *conf)
{
	struct wpabuf *buf;

	buf = dpp_build_conf_start(auth, conf, 1000);
	if (!buf)
		return NULL;

	wpabuf_printf(buf, "\"cred\":{\"akm\":\"%s\",", dpp_akm_str(conf->akm));
	dpp_build_legacy_cred_params(buf, conf);
	wpabuf_put_str(buf, "}}");

	wpa_hexdump_ascii_key(MSG_DEBUG, "DPP: Configuration Object (legacy)",
			      wpabuf_head(buf), wpabuf_len(buf));

	return buf;
}