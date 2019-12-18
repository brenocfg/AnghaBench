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
struct bhnd_nvram_data {int dummy; } ;
typedef  int /*<<< orphan*/  bhnd_nvram_val ;
typedef  int /*<<< orphan*/  bhnd_nvram_type ;

/* Variables and functions */
 int /*<<< orphan*/  BHND_NVRAM_VAL_DYNAMIC ; 
 int /*<<< orphan*/  BHND_NV_LOG (char*,char const*,...) ; 
 int /*<<< orphan*/  BHND_NV_PRINT_WIDTH (size_t) ; 
 int EINVAL ; 
 size_t NVRAM_TLV_ENVP_DATA_MAX_LEN ; 
 int /*<<< orphan*/  bhnd_nvram_trim_path_name (char const*) ; 
 int /*<<< orphan*/  bhnd_nvram_val_bcm_string_fmt ; 
 char* bhnd_nvram_val_bytes (int /*<<< orphan*/ *,size_t*,int /*<<< orphan*/ *) ; 
 int bhnd_nvram_val_convert_new (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bhnd_nvram_val_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bhnd_nvram_validate_name (int /*<<< orphan*/ ) ; 
 int strlen (char const*) ; 

__attribute__((used)) static int
bhnd_nvram_tlv_filter_setvar(struct bhnd_nvram_data *nv, const char *name,
    bhnd_nvram_val *value, bhnd_nvram_val **result)
{
	bhnd_nvram_val	*str;
	const char	*inp;
	bhnd_nvram_type	 itype;
	size_t		 ilen;
	size_t		 name_len, tlv_nremain;
	int		 error;

	tlv_nremain = NVRAM_TLV_ENVP_DATA_MAX_LEN;

	/* Name (trimmed of any path prefix) must be valid */
	if (!bhnd_nvram_validate_name(bhnd_nvram_trim_path_name(name)))
		return (EINVAL);

	/* 'name=' must fit within the maximum TLV_ENV record length */
	name_len = strlen(name) + 1; /* '=' */
	if (tlv_nremain < name_len) {
		BHND_NV_LOG("'%s=' exceeds maximum TLV_ENV record length\n",
		    name);
		return (EINVAL);
	}
	tlv_nremain -= name_len;

	/* Convert value to a (bcm-formatted) string */
	error = bhnd_nvram_val_convert_new(&str, &bhnd_nvram_val_bcm_string_fmt,
	    value, BHND_NVRAM_VAL_DYNAMIC);
	if (error)
		return (error);

	/* The string value must fit within remaining TLV_ENV record length */
	inp = bhnd_nvram_val_bytes(str, &ilen, &itype);
	if (tlv_nremain < ilen) {
		BHND_NV_LOG("'%.*s\\0' exceeds maximum TLV_ENV record length\n",
		    BHND_NV_PRINT_WIDTH(ilen), inp);

		bhnd_nvram_val_release(str);
		return (EINVAL);
	}
	tlv_nremain -= name_len;

	/* Success. Transfer result ownership to the caller. */
	*result = str;
	return (0);
}