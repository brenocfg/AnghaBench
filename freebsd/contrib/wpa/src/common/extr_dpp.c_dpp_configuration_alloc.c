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
struct dpp_configuration {int /*<<< orphan*/  akm; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPP_AKM_DPP ; 
 int /*<<< orphan*/  DPP_AKM_PSK ; 
 int /*<<< orphan*/  DPP_AKM_PSK_SAE ; 
 int /*<<< orphan*/  DPP_AKM_PSK_SAE_DPP ; 
 int /*<<< orphan*/  DPP_AKM_SAE ; 
 int /*<<< orphan*/  DPP_AKM_SAE_DPP ; 
 scalar_t__ bin_str_eq (char const*,size_t,char*) ; 
 int /*<<< orphan*/  dpp_configuration_free (struct dpp_configuration*) ; 
 char* os_strchr (char const*,char) ; 
 size_t os_strlen (char const*) ; 
 struct dpp_configuration* os_zalloc (int) ; 

struct dpp_configuration * dpp_configuration_alloc(const char *type)
{
	struct dpp_configuration *conf;
	const char *end;
	size_t len;

	conf = os_zalloc(sizeof(*conf));
	if (!conf)
		goto fail;

	end = os_strchr(type, ' ');
	if (end)
		len = end - type;
	else
		len = os_strlen(type);

	if (bin_str_eq(type, len, "psk"))
		conf->akm = DPP_AKM_PSK;
	else if (bin_str_eq(type, len, "sae"))
		conf->akm = DPP_AKM_SAE;
	else if (bin_str_eq(type, len, "psk-sae") ||
		 bin_str_eq(type, len, "psk+sae"))
		conf->akm = DPP_AKM_PSK_SAE;
	else if (bin_str_eq(type, len, "sae-dpp") ||
		 bin_str_eq(type, len, "dpp+sae"))
		conf->akm = DPP_AKM_SAE_DPP;
	else if (bin_str_eq(type, len, "psk-sae-dpp") ||
		 bin_str_eq(type, len, "dpp+psk+sae"))
		conf->akm = DPP_AKM_PSK_SAE_DPP;
	else if (bin_str_eq(type, len, "dpp"))
		conf->akm = DPP_AKM_DPP;
	else
		goto fail;

	return conf;
fail:
	dpp_configuration_free(conf);
	return NULL;
}