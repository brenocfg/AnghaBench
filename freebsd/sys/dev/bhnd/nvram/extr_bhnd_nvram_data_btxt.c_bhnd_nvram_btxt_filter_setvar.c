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
typedef  scalar_t__ bhnd_nvram_type ;

/* Variables and functions */
 scalar_t__ BHND_NVRAM_TYPE_STRING ; 
 int /*<<< orphan*/  BHND_NVRAM_VAL_DYNAMIC ; 
 int /*<<< orphan*/  BHND_NV_ASSERT (int,char*) ; 
 int /*<<< orphan*/  BHND_NV_LOG (char*,char const) ; 
 int EINVAL ; 
 int /*<<< orphan*/  bhnd_nvram_trim_path_name (char const*) ; 
 int /*<<< orphan*/  bhnd_nvram_val_bcm_string_fmt ; 
 char* bhnd_nvram_val_bytes (int /*<<< orphan*/ *,size_t*,scalar_t__*) ; 
 int bhnd_nvram_val_convert_new (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bhnd_nvram_val_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bhnd_nvram_validate_name (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bhnd_nvram_btxt_filter_setvar(struct bhnd_nvram_data *nv, const char *name,
    bhnd_nvram_val *value, bhnd_nvram_val **result)
{
	bhnd_nvram_val	*str;
	const char	*inp;
	bhnd_nvram_type	 itype;
	size_t		 ilen;
	int		 error;

	/* Name (trimmed of any path prefix) must be valid */
	if (!bhnd_nvram_validate_name(bhnd_nvram_trim_path_name(name)))
		return (EINVAL);

	/* Value must be bcm-formatted string */
	error = bhnd_nvram_val_convert_new(&str, &bhnd_nvram_val_bcm_string_fmt,
	    value, BHND_NVRAM_VAL_DYNAMIC);
	if (error)
		return (error);

	/* Value string must not contain our record delimiter character ('\n'),
	 * or our comment character ('#') */
	inp = bhnd_nvram_val_bytes(str, &ilen, &itype);
	BHND_NV_ASSERT(itype == BHND_NVRAM_TYPE_STRING, ("non-string value"));
	for (size_t i = 0; i < ilen; i++) {
		switch (inp[i]) {
		case '\n':
		case '#':
			BHND_NV_LOG("invalid character (%#hhx) in value\n",
			    inp[i]);
			bhnd_nvram_val_release(str);
			return (EINVAL);
		}
	}

	/* Success. Transfer result ownership to the caller. */
	*result = str;
	return (0);
}