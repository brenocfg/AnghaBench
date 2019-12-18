#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct bhnd_nvram_store {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  pending; } ;
typedef  TYPE_1__ bhnd_nvstore_path ;
typedef  int /*<<< orphan*/  bhnd_nvram_prop ;

/* Variables and functions */
 int /*<<< orphan*/  BHND_NVSTORE_LOCK_ASSERT (struct bhnd_nvram_store*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/ * bhnd_nvram_plist_get_prop (int /*<<< orphan*/ ,char const*) ; 

bhnd_nvram_prop *
bhnd_nvstore_path_get_update(struct bhnd_nvram_store *sc,
    bhnd_nvstore_path *path, const char *name)
{
	BHND_NVSTORE_LOCK_ASSERT(sc, MA_OWNED);
	return (bhnd_nvram_plist_get_prop(path->pending, name));
}