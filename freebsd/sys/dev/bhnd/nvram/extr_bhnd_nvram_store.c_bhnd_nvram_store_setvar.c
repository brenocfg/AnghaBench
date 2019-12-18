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
typedef  int /*<<< orphan*/  bhnd_nvram_type ;

/* Variables and functions */
 int BHND_NVRAM_VAL_BORROW_DATA ; 
 int BHND_NVRAM_VAL_FIXED ; 
 int /*<<< orphan*/  BHND_NVSTORE_LOCK (struct bhnd_nvram_store*) ; 
 int /*<<< orphan*/  BHND_NVSTORE_UNLOCK (struct bhnd_nvram_store*) ; 
 int /*<<< orphan*/  BHND_NV_LOG (char*,int) ; 
 int EINVAL ; 
 int bhnd_nvram_store_setval_common (struct bhnd_nvram_store*,char const*,int /*<<< orphan*/ *) ; 
 int bhnd_nvram_val_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void const*,size_t,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bhnd_nvram_val_release (int /*<<< orphan*/ *) ; 

int
bhnd_nvram_store_setvar(struct bhnd_nvram_store *sc, const char *name,
    const void *inp, size_t ilen, bhnd_nvram_type itype)
{
	bhnd_nvram_val	val;
	int		error;

	error = bhnd_nvram_val_init(&val, NULL, inp, ilen, itype,
	    BHND_NVRAM_VAL_FIXED|BHND_NVRAM_VAL_BORROW_DATA);
	if (error) {
		BHND_NV_LOG("error initializing value: %d\n", error);
		return (EINVAL);
	}

	BHND_NVSTORE_LOCK(sc);
	error = bhnd_nvram_store_setval_common(sc, name, &val);
	BHND_NVSTORE_UNLOCK(sc);

	bhnd_nvram_val_release(&val);

	return (error);
}