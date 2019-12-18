#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct bhnd_nvram_store {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  value_len; int /*<<< orphan*/  value; } ;
struct TYPE_7__ {TYPE_1__ str; } ;
struct TYPE_8__ {int type; int path_type; TYPE_2__ path; } ;
typedef  TYPE_3__ bhnd_nvstore_name_info ;

/* Variables and functions */
#define  BHND_NVSTORE_ALIAS_DECL 131 
#define  BHND_NVSTORE_PATH_ALIAS 130 
#define  BHND_NVSTORE_PATH_STRING 129 
#define  BHND_NVSTORE_VAR 128 
 int /*<<< orphan*/  BHND_NV_PANIC (char*,int) ; 
 int bhnd_nvstore_register_alias (struct bhnd_nvram_store*,TYPE_3__*,void*) ; 
 int bhnd_nvstore_register_path (struct bhnd_nvram_store*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
bhnd_nvstore_var_register_path(struct bhnd_nvram_store *sc,
    bhnd_nvstore_name_info *info, void *cookiep)
{
	switch (info->type) {
	case BHND_NVSTORE_VAR:
		/* Variable */
		switch (info->path_type) {
		case BHND_NVSTORE_PATH_STRING:
			/* Variable contains a full path string
			 * (pci/1/1/varname); register the path */
			return (bhnd_nvstore_register_path(sc,
			    info->path.str.value, info->path.str.value_len));

		case BHND_NVSTORE_PATH_ALIAS:
			/* Variable contains an alias reference (0:varname).
			 * There's no path to register */
			return (0);
		}

		BHND_NV_PANIC("unsupported path type %d", info->path_type);
		break;

	case BHND_NVSTORE_ALIAS_DECL:
		/* Alias declaration */
		return (bhnd_nvstore_register_alias(sc, info, cookiep));
	}

	BHND_NV_PANIC("unsupported var type %d", info->type);
}