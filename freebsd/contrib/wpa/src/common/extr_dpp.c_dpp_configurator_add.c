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
struct dpp_global {int /*<<< orphan*/  configurator; } ;
struct dpp_configurator {int id; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  bin_clear_free (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  dl_list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dpp_configurator_free (struct dpp_configurator*) ; 
 struct dpp_configurator* dpp_keygen_configurator (char*,int /*<<< orphan*/ *,size_t) ; 
 int dpp_next_configurator_id (struct dpp_global*) ; 
 char* get_param (char const*,char*) ; 
 scalar_t__ hexstr2bin (char*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  os_free (char*) ; 
 int /*<<< orphan*/ * os_malloc (size_t) ; 
 int os_strlen (char*) ; 
 int /*<<< orphan*/  str_clear_free (char*) ; 

int dpp_configurator_add(struct dpp_global *dpp, const char *cmd)
{
	char *curve = NULL;
	char *key = NULL;
	u8 *privkey = NULL;
	size_t privkey_len = 0;
	int ret = -1;
	struct dpp_configurator *conf = NULL;

	curve = get_param(cmd, " curve=");
	key = get_param(cmd, " key=");

	if (key) {
		privkey_len = os_strlen(key) / 2;
		privkey = os_malloc(privkey_len);
		if (!privkey ||
		    hexstr2bin(key, privkey, privkey_len) < 0)
			goto fail;
	}

	conf = dpp_keygen_configurator(curve, privkey, privkey_len);
	if (!conf)
		goto fail;

	conf->id = dpp_next_configurator_id(dpp);
	dl_list_add(&dpp->configurator, &conf->list);
	ret = conf->id;
	conf = NULL;
fail:
	os_free(curve);
	str_clear_free(key);
	bin_clear_free(privkey, privkey_len);
	dpp_configurator_free(conf);
	return ret;
}