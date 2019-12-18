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
struct bhnd_nvram_vardefn {int flags; } ;
struct bhnd_nvram_sprom {int /*<<< orphan*/  state; } ;
struct bhnd_nvram_data {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  vid; } ;
typedef  TYPE_1__ bhnd_sprom_opcode_idx_entry ;

/* Variables and functions */
 int BHND_NVRAM_VF_IGNALL1 ; 
 int /*<<< orphan*/  BHND_NV_ASSERT (int /*<<< orphan*/ ,char*) ; 
 int EINVAL ; 
 int ENOENT ; 
 struct bhnd_nvram_vardefn* bhnd_nvram_get_vardefn (int /*<<< orphan*/ ) ; 
 scalar_t__ bhnd_sprom_is_external_immutable (char const*) ; 
 TYPE_1__* bhnd_sprom_opcode_index_find (int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static int
bhnd_nvram_sprom_filter_unsetvar(struct bhnd_nvram_data *nv, const char *name)
{
	struct bhnd_nvram_sprom		*sp;
	const struct bhnd_nvram_vardefn	*var;
	bhnd_sprom_opcode_idx_entry	*entry;

	sp = (struct bhnd_nvram_sprom *)nv;

	/* Is this an externally immutable variable name? */
	if (bhnd_sprom_is_external_immutable(name))
		return (EINVAL);

	/* Variable must be defined in our SPROM layout */
	if ((entry = bhnd_sprom_opcode_index_find(&sp->state, name)) == NULL)
		return (ENOENT);

	var = bhnd_nvram_get_vardefn(entry->vid);
	BHND_NV_ASSERT(var != NULL, ("missing variable definition"));

	/* Variable must be capable of representing a NULL/deleted value.
	 * 
	 * Since SPROM's layout is fixed, this requires IGNALL -- if
	 * all bits are set, an IGNALL variable is treated as unset. */
	if (!(var->flags & BHND_NVRAM_VF_IGNALL1))
		return (EINVAL);

	return (0);
}