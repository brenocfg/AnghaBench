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
typedef  union bhnd_nvram_sprom_storage {int dummy; } bhnd_nvram_sprom_storage ;
struct bhnd_nvram_data {int dummy; } ;
typedef  int /*<<< orphan*/  bhnd_nvram_val ;

/* Variables and functions */
 int ENOMEM ; 
 int bhnd_nvram_sprom_getvar_common (struct bhnd_nvram_data*,void*,union bhnd_nvram_sprom_storage*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * bhnd_nvram_val_copy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bhnd_nvram_val_release (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
bhnd_nvram_sprom_copy_val(struct bhnd_nvram_data *nv, void *cookiep,
    bhnd_nvram_val **value)
{
	bhnd_nvram_val			val;
	union bhnd_nvram_sprom_storage	storage;
	int				error;

	/* Decode variable to a new value instance */
	error = bhnd_nvram_sprom_getvar_common(nv, cookiep, &storage, &val);
	if (error)
		return (error);

	/* Attempt to copy to heap */
	*value = bhnd_nvram_val_copy(&val);
	bhnd_nvram_val_release(&val);

	if (*value == NULL)
		return (ENOMEM);

	return (0);
}