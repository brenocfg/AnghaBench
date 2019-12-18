#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct dpp_bootstrap_info {int /*<<< orphan*/  uri; int /*<<< orphan*/  type; } ;
struct dpp_authentication {struct dpp_bootstrap_info* own_bi; struct dpp_bootstrap_info* tmp_own_bi; TYPE_2__* peer_bi; } ;
struct TYPE_4__ {TYPE_1__* curve; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPP_BOOTSTRAP_QR_CODE ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  dpp_bootstrap_info_free (struct dpp_bootstrap_info*) ; 
 char* dpp_keygen (struct dpp_bootstrap_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_free (char*) ; 
 int /*<<< orphan*/  os_malloc (size_t) ; 
 int /*<<< orphan*/  os_snprintf (int /*<<< orphan*/ ,size_t,char*,char*) ; 
 scalar_t__ os_strlen (char*) ; 
 struct dpp_bootstrap_info* os_zalloc (int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dpp_autogen_bootstrap_key(struct dpp_authentication *auth)
{
	struct dpp_bootstrap_info *bi;
	char *pk = NULL;
	size_t len;

	if (auth->own_bi)
		return 0; /* already generated */

	bi = os_zalloc(sizeof(*bi));
	if (!bi)
		return -1;
	bi->type = DPP_BOOTSTRAP_QR_CODE;
	pk = dpp_keygen(bi, auth->peer_bi->curve->name, NULL, 0);
	if (!pk)
		goto fail;

	len = 4; /* "DPP:" */
	len += 4 + os_strlen(pk);
	bi->uri = os_malloc(len + 1);
	if (!bi->uri)
		goto fail;
	os_snprintf(bi->uri, len + 1, "DPP:K:%s;;", pk);
	wpa_printf(MSG_DEBUG,
		   "DPP: Auto-generated own bootstrapping key info: URI %s",
		   bi->uri);

	auth->tmp_own_bi = auth->own_bi = bi;

	os_free(pk);

	return 0;
fail:
	os_free(pk);
	dpp_bootstrap_info_free(bi);
	return -1;
}