#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct bhnd_nvram_vardefn {int /*<<< orphan*/  fmt; } ;
struct bhnd_nvram_sprom {int /*<<< orphan*/  state; } ;
struct bhnd_nvram_data {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  vid; } ;
typedef  TYPE_1__ bhnd_sprom_opcode_idx_entry ;
typedef  int /*<<< orphan*/  bhnd_nvram_val ;

/* Variables and functions */
 int /*<<< orphan*/  BHND_NVRAM_VAL_DYNAMIC ; 
 int /*<<< orphan*/  BHND_NV_ASSERT (int /*<<< orphan*/ ,char*) ; 
 int EINVAL ; 
 int ENOENT ; 
 struct bhnd_nvram_vardefn* bhnd_nvram_get_vardefn (int /*<<< orphan*/ ) ; 
 int bhnd_nvram_sprom_write_var (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int bhnd_nvram_val_convert_new (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bhnd_nvram_val_release (int /*<<< orphan*/ *) ; 
 scalar_t__ bhnd_sprom_is_external_immutable (char const*) ; 
 TYPE_1__* bhnd_sprom_opcode_index_find (int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static int
bhnd_nvram_sprom_filter_setvar(struct bhnd_nvram_data *nv, const char *name,
    bhnd_nvram_val *value, bhnd_nvram_val **result)
{
	struct bhnd_nvram_sprom		*sp;
	const struct bhnd_nvram_vardefn	*var;
	bhnd_sprom_opcode_idx_entry	*entry;
	bhnd_nvram_val			*spval;
	int				 error;

	sp = (struct bhnd_nvram_sprom *)nv;

	/* Is this an externally immutable variable name? */
	if (bhnd_sprom_is_external_immutable(name))
		return (EINVAL);

	/* Variable must be defined in our SPROM layout */
	if ((entry = bhnd_sprom_opcode_index_find(&sp->state, name)) == NULL)
		return (ENOENT);

	var = bhnd_nvram_get_vardefn(entry->vid);
	BHND_NV_ASSERT(var != NULL, ("missing variable definition"));

	/* Value must be convertible to the native variable type */
	error = bhnd_nvram_val_convert_new(&spval, var->fmt, value,
	    BHND_NVRAM_VAL_DYNAMIC);
	if (error)
		return (error);

	/* Value must be encodeable by our SPROM layout */
	error = bhnd_nvram_sprom_write_var(&sp->state, entry, spval, NULL);
	if (error) {
		bhnd_nvram_val_release(spval);
		return (error);
	}

	/* Success. Transfer our ownership of the converted value to the
	 * caller */
	*result = spval;
	return (0);
}