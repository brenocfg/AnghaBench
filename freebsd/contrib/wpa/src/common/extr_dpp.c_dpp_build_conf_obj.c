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
struct dpp_authentication {struct dpp_configuration* conf_sta; struct dpp_configuration* conf_ap; scalar_t__ config_obj_override; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 scalar_t__ dpp_akm_dpp (int /*<<< orphan*/ ) ; 
 struct wpabuf* dpp_build_conf_obj_dpp (struct dpp_authentication*,int,struct dpp_configuration*) ; 
 struct wpabuf* dpp_build_conf_obj_legacy (struct dpp_authentication*,int,struct dpp_configuration*) ; 
 int /*<<< orphan*/  os_strlen (scalar_t__) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 struct wpabuf* wpabuf_alloc_copy (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct wpabuf *
dpp_build_conf_obj(struct dpp_authentication *auth, int ap)
{
	struct dpp_configuration *conf;

#ifdef CONFIG_TESTING_OPTIONS
	if (auth->config_obj_override) {
		wpa_printf(MSG_DEBUG, "DPP: Testing - Config Object override");
		return wpabuf_alloc_copy(auth->config_obj_override,
					 os_strlen(auth->config_obj_override));
	}
#endif /* CONFIG_TESTING_OPTIONS */

	conf = ap ? auth->conf_ap : auth->conf_sta;
	if (!conf) {
		wpa_printf(MSG_DEBUG,
			   "DPP: No configuration available for Enrollee(%s) - reject configuration request",
			   ap ? "ap" : "sta");
		return NULL;
	}

	if (dpp_akm_dpp(conf->akm))
		return dpp_build_conf_obj_dpp(auth, ap, conf);
	return dpp_build_conf_obj_legacy(auth, ap, conf);
}