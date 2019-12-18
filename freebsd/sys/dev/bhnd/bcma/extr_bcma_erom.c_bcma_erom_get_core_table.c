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
typedef  scalar_t__ u_int ;
struct bhnd_core_info {scalar_t__ vendor; scalar_t__ device; } ;
struct bcma_erom_core {int dummy; } ;
struct bcma_erom {int dummy; } ;
typedef  int /*<<< orphan*/  bus_size_t ;
typedef  int /*<<< orphan*/  bhnd_erom_t ;

/* Variables and functions */
 int /*<<< orphan*/  BCMA_EROM_ENTRY_TYPE_CORE ; 
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  M_BHND ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int bcma_erom_parse_core (struct bcma_erom*,struct bcma_erom_core*) ; 
 int /*<<< orphan*/  bcma_erom_reset (struct bcma_erom*) ; 
 int /*<<< orphan*/  bcma_erom_seek (struct bcma_erom*,int /*<<< orphan*/ ) ; 
 int bcma_erom_seek_next (struct bcma_erom*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcma_erom_tell (struct bcma_erom*) ; 
 int /*<<< orphan*/  bcma_erom_to_core_info (struct bcma_erom_core*,scalar_t__,int,struct bhnd_core_info*) ; 
 int /*<<< orphan*/  free (struct bhnd_core_info*,int /*<<< orphan*/ ) ; 
 struct bhnd_core_info* mallocarray (scalar_t__,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bcma_erom_get_core_table(bhnd_erom_t *erom, struct bhnd_core_info **cores,
    u_int *num_cores)
{
	struct bcma_erom	*sc;
	struct bhnd_core_info	*buffer;
	bus_size_t		 initial_offset;
	u_int			 count;
	int			 error;

	sc = (struct bcma_erom *)erom;

	buffer = NULL;
	initial_offset = bcma_erom_tell(sc);

	/* Determine the core count */
	bcma_erom_reset(sc);
	for (count = 0, error = 0; !error; count++) {
		struct bcma_erom_core core;

		/* Seek to the first readable core entry */
		error = bcma_erom_seek_next(sc, BCMA_EROM_ENTRY_TYPE_CORE);
		if (error == ENOENT)
			break;
		else if (error)
			goto cleanup;
		
		/* Read past the core descriptor */
		if ((error = bcma_erom_parse_core(sc, &core)))
			goto cleanup;
	}

	/* Allocate our output buffer */
	buffer = mallocarray(count, sizeof(struct bhnd_core_info), M_BHND,
	    M_NOWAIT);
	if (buffer == NULL) {
		error = ENOMEM;
		goto cleanup;
	}

	/* Parse all core descriptors */
	bcma_erom_reset(sc);
	for (u_int i = 0; i < count; i++) {
		struct bcma_erom_core	core;
		int			unit;

		/* Parse the core */
		error = bcma_erom_seek_next(sc, BCMA_EROM_ENTRY_TYPE_CORE);
		if (error)
			goto cleanup;

		error = bcma_erom_parse_core(sc, &core);
		if (error)
			goto cleanup;

		/* Determine the unit number */
		unit = 0;
		for (u_int j = 0; j < i; j++) {
			if (buffer[i].vendor == buffer[j].vendor &&
			    buffer[i].device == buffer[j].device)
				unit++;
		}

		/* Convert to a bhnd info record */
		bcma_erom_to_core_info(&core, i, unit, &buffer[i]);
	}

cleanup:
	if (!error) {
		*cores = buffer;
		*num_cores = count;
	} else {
		if (buffer != NULL)
			free(buffer, M_BHND);
	}

	/* Restore the initial position */
	bcma_erom_seek(sc, initial_offset);
	return (error);
}