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
typedef  char u8 ;
struct dpp_configuration {size_t ssid_len; char* ssid; char* psk; int psk_set; char* group_id; long netaccesskey_expiry; scalar_t__ passphrase; } ;
struct dpp_authentication {struct dpp_configuration* conf_ap; struct dpp_configuration* conf_sta; } ;

/* Variables and functions */
 size_t PMK_LEN ; 
 struct dpp_configuration* dpp_configuration_alloc (char const*) ; 
 int /*<<< orphan*/  dpp_configuration_free (struct dpp_configuration*) ; 
 int /*<<< orphan*/  dpp_configuration_valid (struct dpp_configuration*) ; 
 scalar_t__ hexstr2bin (char const*,char*,size_t) ; 
 char* os_malloc (size_t) ; 
 int /*<<< orphan*/  os_memcpy (char*,char const*,size_t) ; 
 char* os_strchr (char const*,char) ; 
 size_t os_strlen (char const*) ; 
 char* os_strstr (char const*,char*) ; 
 scalar_t__ os_zalloc (size_t) ; 
 long strtol (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dpp_configuration_parse(struct dpp_authentication *auth,
				   const char *cmd)
{
	const char *pos, *end;
	struct dpp_configuration *conf_sta = NULL, *conf_ap = NULL;
	struct dpp_configuration *conf = NULL;

	pos = os_strstr(cmd, " conf=sta-");
	if (pos) {
		conf_sta = dpp_configuration_alloc(pos + 10);
		if (!conf_sta)
			goto fail;
		conf = conf_sta;
	}

	pos = os_strstr(cmd, " conf=ap-");
	if (pos) {
		conf_ap = dpp_configuration_alloc(pos + 9);
		if (!conf_ap)
			goto fail;
		conf = conf_ap;
	}

	if (!conf)
		return 0;

	pos = os_strstr(cmd, " ssid=");
	if (pos) {
		pos += 6;
		end = os_strchr(pos, ' ');
		conf->ssid_len = end ? (size_t) (end - pos) : os_strlen(pos);
		conf->ssid_len /= 2;
		if (conf->ssid_len > sizeof(conf->ssid) ||
		    hexstr2bin(pos, conf->ssid, conf->ssid_len) < 0)
			goto fail;
	} else {
#ifdef CONFIG_TESTING_OPTIONS
		/* use a default SSID for legacy testing reasons */
		os_memcpy(conf->ssid, "test", 4);
		conf->ssid_len = 4;
#else /* CONFIG_TESTING_OPTIONS */
		goto fail;
#endif /* CONFIG_TESTING_OPTIONS */
	}

	pos = os_strstr(cmd, " pass=");
	if (pos) {
		size_t pass_len;

		pos += 6;
		end = os_strchr(pos, ' ');
		pass_len = end ? (size_t) (end - pos) : os_strlen(pos);
		pass_len /= 2;
		if (pass_len > 63 || pass_len < 8)
			goto fail;
		conf->passphrase = os_zalloc(pass_len + 1);
		if (!conf->passphrase ||
		    hexstr2bin(pos, (u8 *) conf->passphrase, pass_len) < 0)
			goto fail;
	}

	pos = os_strstr(cmd, " psk=");
	if (pos) {
		pos += 5;
		if (hexstr2bin(pos, conf->psk, PMK_LEN) < 0)
			goto fail;
		conf->psk_set = 1;
	}

	pos = os_strstr(cmd, " group_id=");
	if (pos) {
		size_t group_id_len;

		pos += 10;
		end = os_strchr(pos, ' ');
		group_id_len = end ? (size_t) (end - pos) : os_strlen(pos);
		conf->group_id = os_malloc(group_id_len + 1);
		if (!conf->group_id)
			goto fail;
		os_memcpy(conf->group_id, pos, group_id_len);
		conf->group_id[group_id_len] = '\0';
	}

	pos = os_strstr(cmd, " expiry=");
	if (pos) {
		long int val;

		pos += 8;
		val = strtol(pos, NULL, 0);
		if (val <= 0)
			goto fail;
		conf->netaccesskey_expiry = val;
	}

	if (!dpp_configuration_valid(conf))
		goto fail;

	auth->conf_sta = conf_sta;
	auth->conf_ap = conf_ap;
	return 0;

fail:
	dpp_configuration_free(conf_sta);
	dpp_configuration_free(conf_ap);
	return -1;
}