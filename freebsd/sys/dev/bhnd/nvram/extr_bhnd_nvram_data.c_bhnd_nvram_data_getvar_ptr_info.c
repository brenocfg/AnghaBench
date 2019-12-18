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
struct bhnd_nvram_vardefn {int /*<<< orphan*/ * fmt; } ;
struct bhnd_nvram_data {int dummy; } ;
typedef  int /*<<< orphan*/  bhnd_nvram_val_fmt ;
typedef  scalar_t__ bhnd_nvram_type ;

/* Variables and functions */
 int BHND_NVRAM_DATA_CAP_DEVPATHS ; 
 int BHND_NVRAM_DATA_CAP_READ_PTR ; 
 scalar_t__ BHND_NVRAM_TYPE_STRING ; 
 int /*<<< orphan*/  BHND_NV_ASSERT (int,char*) ; 
 int bhnd_nvram_data_caps (struct bhnd_nvram_data*) ; 
 char* bhnd_nvram_data_getvar_name (struct bhnd_nvram_data*,void*) ; 
 void* bhnd_nvram_data_getvar_ptr (struct bhnd_nvram_data*,void*,size_t*,scalar_t__*) ; 
 struct bhnd_nvram_vardefn* bhnd_nvram_find_vardefn (char const*) ; 
 char* bhnd_nvram_trim_path_name (char const*) ; 
 int /*<<< orphan*/  bhnd_nvram_val_bcm_string_fmt ; 
 int /*<<< orphan*/ * bhnd_nvram_val_default_fmt (scalar_t__) ; 

__attribute__((used)) static const void *
bhnd_nvram_data_getvar_ptr_info(struct bhnd_nvram_data *nv, void *cookiep,
    size_t *len, bhnd_nvram_type *type, const bhnd_nvram_val_fmt **fmt)
{
	const struct bhnd_nvram_vardefn	*vdefn;
	const char			*name;
	const void			*vptr;

	BHND_NV_ASSERT(bhnd_nvram_data_caps(nv) & BHND_NVRAM_DATA_CAP_READ_PTR,
	    ("instance does not advertise READ_PTR support"));

	/* Fetch pointer to variable data */
	vptr = bhnd_nvram_data_getvar_ptr(nv, cookiep, len, type);
	if (vptr == NULL)
		return (NULL);

	/* Select a default value format implementation */


	/* Fetch the reference variable name */
	name = bhnd_nvram_data_getvar_name(nv, cookiep);

	/* Trim path prefix, if any; the Broadcom NVRAM format assumes a global
	 * namespace for all variable definitions */
	if (bhnd_nvram_data_caps(nv) & BHND_NVRAM_DATA_CAP_DEVPATHS)
		name = bhnd_nvram_trim_path_name(name);

	/* Check the variable definition table for a matching entry; if
	 * it exists, use it to populate the value format. */
	vdefn = bhnd_nvram_find_vardefn(name);
	if (vdefn != NULL) {
		BHND_NV_ASSERT(vdefn->fmt != NULL,
		    ("NULL format for %s", name));
		*fmt = vdefn->fmt;
	} else if (*type == BHND_NVRAM_TYPE_STRING) {
		/* Default to Broadcom-specific string interpretation */
		*fmt = &bhnd_nvram_val_bcm_string_fmt;
	} else {
		/* Fall back on native formatting */
		*fmt = bhnd_nvram_val_default_fmt(*type);
	}

	return (vptr);
}