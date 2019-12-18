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
typedef  int /*<<< orphan*/  bhnd_nvram_type ;

/* Variables and functions */
 int bhnd_nvram_sprom_getvar_common (struct bhnd_nvram_data*,void*,union bhnd_nvram_sprom_storage*,int /*<<< orphan*/ *) ; 
 int bhnd_nvram_val_encode (int /*<<< orphan*/ *,void*,size_t*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bhnd_nvram_val_release (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
bhnd_nvram_sprom_getvar(struct bhnd_nvram_data *nv, void *cookiep, void *buf,
    size_t *len, bhnd_nvram_type otype)
{
	bhnd_nvram_val			val;
	union bhnd_nvram_sprom_storage	storage;
	int				error;

	/* Decode variable to a new value instance */
	error = bhnd_nvram_sprom_getvar_common(nv, cookiep, &storage, &val);
	if (error)
		return (error);

	/* Perform value coercion */
	error = bhnd_nvram_val_encode(&val, buf, len, otype);

	/* Clean up */
	bhnd_nvram_val_release(&val);
	return (error);
}