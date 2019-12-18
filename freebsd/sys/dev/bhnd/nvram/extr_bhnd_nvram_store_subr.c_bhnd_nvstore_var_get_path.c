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
struct bhnd_nvram_store {int dummy; } ;
typedef  int /*<<< orphan*/  bhnd_nvstore_path ;
struct TYPE_7__ {int /*<<< orphan*/  value; } ;
struct TYPE_6__ {int /*<<< orphan*/  value_len; int /*<<< orphan*/  value; } ;
struct TYPE_8__ {TYPE_2__ alias; TYPE_1__ str; } ;
struct TYPE_9__ {int path_type; TYPE_3__ path; } ;
typedef  TYPE_4__ bhnd_nvstore_name_info ;

/* Variables and functions */
#define  BHND_NVSTORE_PATH_ALIAS 129 
#define  BHND_NVSTORE_PATH_STRING 128 
 int /*<<< orphan*/  BHND_NV_PANIC (char*,int) ; 
 int /*<<< orphan*/ * bhnd_nvstore_get_path (struct bhnd_nvram_store*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * bhnd_nvstore_resolve_path_alias (struct bhnd_nvram_store*,int /*<<< orphan*/ ) ; 

bhnd_nvstore_path *
bhnd_nvstore_var_get_path(struct bhnd_nvram_store *sc,
    bhnd_nvstore_name_info *info)
{
	switch (info->path_type) {
	case BHND_NVSTORE_PATH_STRING:
		return (bhnd_nvstore_get_path(sc, info->path.str.value,
		    info->path.str.value_len));
	case BHND_NVSTORE_PATH_ALIAS:
		return (bhnd_nvstore_resolve_path_alias(sc,
		    info->path.alias.value));
	}

	BHND_NV_PANIC("unsupported path type %d", info->path_type);
}