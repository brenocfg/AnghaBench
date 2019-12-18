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
struct bhnd_nvram_store {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BHND_NVRAM_VAL_NULL ; 
 int /*<<< orphan*/  BHND_NVSTORE_LOCK (struct bhnd_nvram_store*) ; 
 int /*<<< orphan*/  BHND_NVSTORE_UNLOCK (struct bhnd_nvram_store*) ; 
 int bhnd_nvram_store_setval_common (struct bhnd_nvram_store*,char const*,int /*<<< orphan*/ ) ; 

int
bhnd_nvram_store_unsetvar(struct bhnd_nvram_store *sc, const char *name)
{
	int error;

	BHND_NVSTORE_LOCK(sc);
	error = bhnd_nvram_store_setval_common(sc, name, BHND_NVRAM_VAL_NULL);
	BHND_NVSTORE_UNLOCK(sc);

	return (error);
}