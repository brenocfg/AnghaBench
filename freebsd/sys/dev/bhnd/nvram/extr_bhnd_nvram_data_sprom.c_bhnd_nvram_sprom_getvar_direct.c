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
typedef  union bhnd_nvram_sprom_storage {int dummy; } bhnd_nvram_sprom_storage ;
struct bhnd_nvram_vardefn {int dummy; } ;
struct bhnd_nvram_io {int dummy; } ;
typedef  int /*<<< orphan*/  bhnd_sprom_opcode_state ;
struct TYPE_4__ {size_t vid; } ;
typedef  TYPE_1__ bhnd_sprom_opcode_idx_entry ;
typedef  int /*<<< orphan*/  bhnd_sprom_layout ;
typedef  int /*<<< orphan*/  bhnd_nvram_val ;
typedef  int /*<<< orphan*/  bhnd_nvram_type ;

/* Variables and functions */
 int /*<<< orphan*/  BHND_NV_LOG (char*,int) ; 
 int ENOENT ; 
 int ENXIO ; 
 struct bhnd_nvram_vardefn* bhnd_nvram_find_vardefn (char const*) ; 
 size_t bhnd_nvram_get_vardefn_id (struct bhnd_nvram_vardefn const*) ; 
 int bhnd_nvram_sprom_ident (struct bhnd_nvram_io*,int /*<<< orphan*/  const**) ; 
 int bhnd_nvram_sprom_read_var (int /*<<< orphan*/ *,TYPE_1__*,struct bhnd_nvram_io*,union bhnd_nvram_sprom_storage*,int /*<<< orphan*/ *) ; 
 int bhnd_nvram_val_encode (int /*<<< orphan*/ *,void*,size_t*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bhnd_nvram_val_release (int /*<<< orphan*/ *) ; 
 int bhnd_sprom_opcode_init (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int bhnd_sprom_opcode_init_entry (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int bhnd_sprom_opcode_next_var (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
bhnd_nvram_sprom_getvar_direct(struct bhnd_nvram_io *io, const char *name,
    void *buf, size_t *len, bhnd_nvram_type type)
{
	const bhnd_sprom_layout		*layout;
	bhnd_sprom_opcode_state		 state;
	const struct bhnd_nvram_vardefn	*var;
	size_t				 vid;
	int				 error;

	/* Look up the variable definition and ID */
	if ((var = bhnd_nvram_find_vardefn(name)) == NULL)
		return (ENOENT);
	
	vid = bhnd_nvram_get_vardefn_id(var);

	/* Identify the SPROM image layout */
	if ((error = bhnd_nvram_sprom_ident(io, &layout)))
		return (error);

	/* Initialize SPROM layout interpreter */
	if ((error = bhnd_sprom_opcode_init(&state, layout))) {
		BHND_NV_LOG("error initializing opcode state: %d\n", error);
		return (ENXIO);
	}

	/* Find SPROM layout entry for the requested variable */
	while ((error = bhnd_sprom_opcode_next_var(&state)) == 0) {
		bhnd_sprom_opcode_idx_entry	entry;
		union bhnd_nvram_sprom_storage	storage;
		bhnd_nvram_val			val;
	
		/* Fetch the variable's entry state */
		if ((error = bhnd_sprom_opcode_init_entry(&state, &entry)))
			return (error);

		/* Match against expected VID */
		if (entry.vid != vid)
			continue;

		/* Decode variable to a new value instance */
		error = bhnd_nvram_sprom_read_var(&state, &entry, io, &storage,
		    &val);
		if (error)
			return (error);

		/* Perform value coercion */
		error = bhnd_nvram_val_encode(&val, buf, len, type);

		/* Clean up */
		bhnd_nvram_val_release(&val);
		return (error);
	}

	/* Hit EOF without matching the requested variable? */
	if (error == ENOENT)
		return (ENOENT);

	/* Some other parse error occured */
	return (error);
}