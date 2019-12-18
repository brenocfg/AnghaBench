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
struct dpp_authentication {int /*<<< orphan*/  groups_override; int /*<<< orphan*/  discovery_override; int /*<<< orphan*/  config_obj_override; int /*<<< orphan*/  tmp_own_bi; int /*<<< orphan*/  c_sign_key; int /*<<< orphan*/  net_access_key; int /*<<< orphan*/  connector; int /*<<< orphan*/  conf_req; int /*<<< orphan*/  resp_msg; int /*<<< orphan*/  req_msg; int /*<<< orphan*/  peer_protocol_key; int /*<<< orphan*/  own_protocol_key; int /*<<< orphan*/  conf_sta; int /*<<< orphan*/  conf_ap; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_PKEY_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bin_clear_free (struct dpp_authentication*,int) ; 
 int /*<<< orphan*/  dpp_bootstrap_info_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dpp_configuration_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpabuf_free (int /*<<< orphan*/ ) ; 

void dpp_auth_deinit(struct dpp_authentication *auth)
{
	if (!auth)
		return;
	dpp_configuration_free(auth->conf_ap);
	dpp_configuration_free(auth->conf_sta);
	EVP_PKEY_free(auth->own_protocol_key);
	EVP_PKEY_free(auth->peer_protocol_key);
	wpabuf_free(auth->req_msg);
	wpabuf_free(auth->resp_msg);
	wpabuf_free(auth->conf_req);
	os_free(auth->connector);
	wpabuf_free(auth->net_access_key);
	wpabuf_free(auth->c_sign_key);
	dpp_bootstrap_info_free(auth->tmp_own_bi);
#ifdef CONFIG_TESTING_OPTIONS
	os_free(auth->config_obj_override);
	os_free(auth->discovery_override);
	os_free(auth->groups_override);
#endif /* CONFIG_TESTING_OPTIONS */
	bin_clear_free(auth, sizeof(*auth));
}