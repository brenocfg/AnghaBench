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
typedef  int /*<<< orphan*/  bhnd_nvram_val ;

/* Variables and functions */
 int /*<<< orphan*/  BHND_NVSTORE_LOCK (struct bhnd_nvram_store*) ; 
 int /*<<< orphan*/  BHND_NVSTORE_UNLOCK (struct bhnd_nvram_store*) ; 
 int bhnd_nvram_store_setval_common (struct bhnd_nvram_store*,char const*,int /*<<< orphan*/ *) ; 

int
bhnd_nvram_store_setval(struct bhnd_nvram_store *sc, const char *name,
    bhnd_nvram_val *value)
{
	int error;

	BHND_NVSTORE_LOCK(sc);
	error = bhnd_nvram_store_setval_common(sc, name, value);
	BHND_NVSTORE_UNLOCK(sc);

	return (error);
}