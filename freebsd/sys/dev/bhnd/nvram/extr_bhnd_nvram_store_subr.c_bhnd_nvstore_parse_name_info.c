#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  void* u_long ;
typedef  scalar_t__ bhnd_nvstore_name_type ;
struct TYPE_7__ {char const* value; size_t value_len; } ;
struct TYPE_6__ {void* value; } ;
struct TYPE_8__ {TYPE_2__ str; TYPE_1__ alias; } ;
struct TYPE_9__ {char const* name; TYPE_3__ path; void* path_type; void* type; } ;
typedef  TYPE_4__ bhnd_nvstore_name_info ;

/* Variables and functions */
 int BHND_NVRAM_DATA_CAP_DEVPATHS ; 
 void* BHND_NVSTORE_ALIAS_DECL ; 
 scalar_t__ BHND_NVSTORE_NAME_INTERNAL ; 
 void* BHND_NVSTORE_PATH_ALIAS ; 
 void* BHND_NVSTORE_PATH_STRING ; 
 char const* BHND_NVSTORE_ROOT_PATH ; 
 size_t BHND_NVSTORE_ROOT_PATH_LEN ; 
 void* BHND_NVSTORE_VAR ; 
 int ENOENT ; 
 scalar_t__ bhnd_nv_isdigit (char const) ; 
 int /*<<< orphan*/  bhnd_nvram_validate_name (char const*) ; 
 int strlen (char*) ; 
 scalar_t__ strncmp (char const*,char*,int) ; 
 char* strrchr (char const*,char) ; 
 void* strtoul (char const*,char**,int) ; 

int
bhnd_nvstore_parse_name_info(const char *name, bhnd_nvstore_name_type type,
    uint32_t data_caps, bhnd_nvstore_name_info *info)
{
	const char	*p;
	char		*endp;

	/* Skip path parsing? */
	if (data_caps & BHND_NVRAM_DATA_CAP_DEVPATHS) {
		/* devpath declaration? (devpath0=pci/1/1) */
		if (strncmp(name, "devpath", strlen("devpath")) == 0) {
			u_long alias;

			/* Perform standard validation on the relative
			 * variable name */
			if (type != BHND_NVSTORE_NAME_INTERNAL &&
			    !bhnd_nvram_validate_name(name))
			{
				return (ENOENT);
			}

			/* Parse alias value that should follow a 'devpath'
			 * prefix */
			p = name + strlen("devpath");
			alias = strtoul(p, &endp, 10);
			if (endp != p && *endp == '\0') {
				info->type = BHND_NVSTORE_ALIAS_DECL;
				info->path_type = BHND_NVSTORE_PATH_ALIAS;
				info->name = name;
				info->path.alias.value = alias;

				return (0);
			}
		}

		/* device aliased variable? (0:varname) */
		if (bhnd_nv_isdigit(*name)) {
			u_long alias;

			/* Parse '0:' alias prefix */
			alias = strtoul(name, &endp, 10);
			if (endp != name && *endp == ':') {
				/* Perform standard validation on the relative
				 * variable name */
				if (type != BHND_NVSTORE_NAME_INTERNAL &&
				    !bhnd_nvram_validate_name(name))
				{
					return (ENOENT);
				}

				info->type = BHND_NVSTORE_VAR;
				info->path_type = BHND_NVSTORE_PATH_ALIAS;

				/* name follows 0: prefix */
				info->name = endp + 1;
				info->path.alias.value = alias;

				return (0);
			}
		}

		/* device variable? (pci/1/1/varname) */
		if ((p = strrchr(name, '/')) != NULL) {
			const char	*path, *relative_name;
			size_t		 path_len;

			/* Determine the path length; 'p' points at the last
			 * path separator in 'name' */
			path_len = p - name;
			path = name;

			/* The relative variable name directly follows the
			 * final path separator '/' */
			relative_name = path + path_len + 1;

			/* Now that we calculated the name offset, exclude all
			 * trailing '/' characters from the path length */
			while (path_len > 0 && path[path_len-1] == '/')
				path_len--;

			/* Perform standard validation on the relative
			 * variable name */
			if (type != BHND_NVSTORE_NAME_INTERNAL &&
			    !bhnd_nvram_validate_name(relative_name))
			{
				return (ENOENT);
			}

			/* Initialize result with pointers into the name
			 * buffer */
			info->type = BHND_NVSTORE_VAR;
			info->path_type = BHND_NVSTORE_PATH_STRING;
			info->name = relative_name;
			info->path.str.value = path;
			info->path.str.value_len = path_len;

			return (0);
		}
	}

	/* If all other parsing fails, the result is a simple variable with
	 * an implicit path of "/" */
	if (type != BHND_NVSTORE_NAME_INTERNAL &&
	    !bhnd_nvram_validate_name(name))
	{
		/* Invalid relative name */
		return (ENOENT);
	}

	info->type = BHND_NVSTORE_VAR;
	info->path_type = BHND_NVSTORE_PATH_STRING;
	info->name = name;
	info->path.str.value = BHND_NVSTORE_ROOT_PATH;
	info->path.str.value_len = BHND_NVSTORE_ROOT_PATH_LEN;

	return (0);
}