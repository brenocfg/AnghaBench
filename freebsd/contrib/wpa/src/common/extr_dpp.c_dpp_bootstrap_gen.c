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
typedef  int /*<<< orphan*/  u8 ;
struct dpp_global {int /*<<< orphan*/  bootstrap; } ;
struct dpp_bootstrap_info {int id; int /*<<< orphan*/  list; void* uri; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPP_BOOTSTRAP_PKEX ; 
 int /*<<< orphan*/  DPP_BOOTSTRAP_QR_CODE ; 
 int /*<<< orphan*/  bin_clear_free (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  dl_list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dpp_bootstrap_info_free (struct dpp_bootstrap_info*) ; 
 char* dpp_keygen (struct dpp_bootstrap_info*,char*,int /*<<< orphan*/ *,size_t) ; 
 int dpp_next_id (struct dpp_global*) ; 
 scalar_t__ dpp_parse_uri_chan_list (struct dpp_bootstrap_info*,char*) ; 
 scalar_t__ dpp_parse_uri_info (struct dpp_bootstrap_info*,char*) ; 
 scalar_t__ dpp_parse_uri_mac (struct dpp_bootstrap_info*,char*) ; 
 char* get_param (char const*,char*) ; 
 scalar_t__ hexstr2bin (char*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  os_free (char*) ; 
 void* os_malloc (size_t) ; 
 int /*<<< orphan*/  os_snprintf (void*,size_t,char*,char*,char*,char*,char*,char*,char*,char*,char*,char*,char*) ; 
 int os_strlen (char*) ; 
 scalar_t__ os_strstr (char const*,char*) ; 
 struct dpp_bootstrap_info* os_zalloc (int) ; 
 int /*<<< orphan*/  str_clear_free (char*) ; 

int dpp_bootstrap_gen(struct dpp_global *dpp, const char *cmd)
{
	char *chan = NULL, *mac = NULL, *info = NULL, *pk = NULL, *curve = NULL;
	char *key = NULL;
	u8 *privkey = NULL;
	size_t privkey_len = 0;
	size_t len;
	int ret = -1;
	struct dpp_bootstrap_info *bi;

	if (!dpp)
		return -1;

	bi = os_zalloc(sizeof(*bi));
	if (!bi)
		goto fail;

	if (os_strstr(cmd, "type=qrcode"))
		bi->type = DPP_BOOTSTRAP_QR_CODE;
	else if (os_strstr(cmd, "type=pkex"))
		bi->type = DPP_BOOTSTRAP_PKEX;
	else
		goto fail;

	chan = get_param(cmd, " chan=");
	mac = get_param(cmd, " mac=");
	info = get_param(cmd, " info=");
	curve = get_param(cmd, " curve=");
	key = get_param(cmd, " key=");

	if (key) {
		privkey_len = os_strlen(key) / 2;
		privkey = os_malloc(privkey_len);
		if (!privkey ||
		    hexstr2bin(key, privkey, privkey_len) < 0)
			goto fail;
	}

	pk = dpp_keygen(bi, curve, privkey, privkey_len);
	if (!pk)
		goto fail;

	len = 4; /* "DPP:" */
	if (chan) {
		if (dpp_parse_uri_chan_list(bi, chan) < 0)
			goto fail;
		len += 3 + os_strlen(chan); /* C:...; */
	}
	if (mac) {
		if (dpp_parse_uri_mac(bi, mac) < 0)
			goto fail;
		len += 3 + os_strlen(mac); /* M:...; */
	}
	if (info) {
		if (dpp_parse_uri_info(bi, info) < 0)
			goto fail;
		len += 3 + os_strlen(info); /* I:...; */
	}
	len += 4 + os_strlen(pk);
	bi->uri = os_malloc(len + 1);
	if (!bi->uri)
		goto fail;
	os_snprintf(bi->uri, len + 1, "DPP:%s%s%s%s%s%s%s%s%sK:%s;;",
		    chan ? "C:" : "", chan ? chan : "", chan ? ";" : "",
		    mac ? "M:" : "", mac ? mac : "", mac ? ";" : "",
		    info ? "I:" : "", info ? info : "", info ? ";" : "",
		    pk);
	bi->id = dpp_next_id(dpp);
	dl_list_add(&dpp->bootstrap, &bi->list);
	ret = bi->id;
	bi = NULL;
fail:
	os_free(curve);
	os_free(pk);
	os_free(chan);
	os_free(mac);
	os_free(info);
	str_clear_free(key);
	bin_clear_free(privkey, privkey_len);
	dpp_bootstrap_info_free(bi);
	return ret;
}