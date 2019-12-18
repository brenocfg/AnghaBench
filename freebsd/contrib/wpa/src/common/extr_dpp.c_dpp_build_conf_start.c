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
struct dpp_configuration {int /*<<< orphan*/  ssid_len; scalar_t__ ssid; } ;
struct dpp_authentication {char* discovery_override; } ;
typedef  int /*<<< orphan*/  ssid ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  json_escape_string (char*,int,char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ os_strlen (char*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,char*) ; 
 struct wpabuf* wpabuf_alloc (int) ; 
 int /*<<< orphan*/  wpabuf_put_str (struct wpabuf*,char*) ; 
 int /*<<< orphan*/  wpabuf_put_u8 (struct wpabuf*,char) ; 

__attribute__((used)) static struct wpabuf *
dpp_build_conf_start(struct dpp_authentication *auth,
		     struct dpp_configuration *conf, size_t tailroom)
{
	struct wpabuf *buf;
	char ssid[6 * sizeof(conf->ssid) + 1];

#ifdef CONFIG_TESTING_OPTIONS
	if (auth->discovery_override)
		tailroom += os_strlen(auth->discovery_override);
#endif /* CONFIG_TESTING_OPTIONS */

	buf = wpabuf_alloc(200 + tailroom);
	if (!buf)
		return NULL;
	wpabuf_put_str(buf, "{\"wi-fi_tech\":\"infra\",\"discovery\":");
#ifdef CONFIG_TESTING_OPTIONS
	if (auth->discovery_override) {
		wpa_printf(MSG_DEBUG, "DPP: TESTING - discovery override: '%s'",
			   auth->discovery_override);
		wpabuf_put_str(buf, auth->discovery_override);
		wpabuf_put_u8(buf, ',');
		return buf;
	}
#endif /* CONFIG_TESTING_OPTIONS */
	wpabuf_put_str(buf, "{\"ssid\":\"");
	json_escape_string(ssid, sizeof(ssid),
			   (const char *) conf->ssid, conf->ssid_len);
	wpabuf_put_str(buf, ssid);
	wpabuf_put_str(buf, "\"},");

	return buf;
}