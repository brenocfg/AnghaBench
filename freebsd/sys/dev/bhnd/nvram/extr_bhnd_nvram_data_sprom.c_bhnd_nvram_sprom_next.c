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
struct bhnd_nvram_vardefn {int flags; char const* name; int /*<<< orphan*/  type; } ;
struct bhnd_nvram_sprom {int /*<<< orphan*/  state; } ;
struct bhnd_nvram_data {int dummy; } ;
typedef  void bhnd_sprom_opcode_idx_entry ;

/* Variables and functions */
 int BHND_NVRAM_VF_IGNALL1 ; 
 int /*<<< orphan*/  BHND_NV_ASSERT (int,char*) ; 
 int ENOENT ; 
 struct bhnd_nvram_vardefn* SPROM_COOKIE_TO_NVRAM_VAR (void*) ; 
 int bhnd_nvram_sprom_getvar (struct bhnd_nvram_data*,void*,int /*<<< orphan*/ *,size_t*,int /*<<< orphan*/ ) ; 
 void* bhnd_sprom_opcode_index_next (int /*<<< orphan*/ *,void*) ; 

__attribute__((used)) static const char *
bhnd_nvram_sprom_next(struct bhnd_nvram_data *nv, void **cookiep)
{
	struct bhnd_nvram_sprom		*sp;
	bhnd_sprom_opcode_idx_entry	*entry;
	const struct bhnd_nvram_vardefn	*var;

	sp = (struct bhnd_nvram_sprom *)nv;

	/* Find next index entry that is not disabled by virtue of IGNALL1 */
	entry = *cookiep;
	while ((entry = bhnd_sprom_opcode_index_next(&sp->state, entry))) {
		/* Update cookiep and fetch variable definition */
		*cookiep = entry;
		var = SPROM_COOKIE_TO_NVRAM_VAR(*cookiep);
		BHND_NV_ASSERT(var != NULL, ("invalid cookiep %p", cookiep));

		/* We might need to parse the variable's value to determine
		 * whether it should be treated as unset */
		if (var->flags & BHND_NVRAM_VF_IGNALL1) {
			int     error;
			size_t  len;

			error = bhnd_nvram_sprom_getvar(nv, *cookiep, NULL,
			    &len, var->type);
			if (error) {
				BHND_NV_ASSERT(error == ENOENT, ("unexpected "
				    "error parsing variable: %d", error));
				continue;
			}
		}

		/* Found! */
		return (var->name);
	}

	/* Reached end of index entries */
	return (NULL);
}