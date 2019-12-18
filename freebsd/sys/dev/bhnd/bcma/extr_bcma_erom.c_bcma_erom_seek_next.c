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
typedef  int uint8_t ;
typedef  scalar_t__ uint32_t ;
struct bcma_erom {int dummy; } ;

/* Variables and functions */
#define  BCMA_EROM_ENTRY_TYPE_CORE 130 
#define  BCMA_EROM_ENTRY_TYPE_MPORT 129 
#define  BCMA_EROM_ENTRY_TYPE_REGION 128 
 int BCMA_EROM_GET_ATTR (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ BCMA_EROM_TABLE_EOF ; 
 int EINVAL ; 
 int ENOENT ; 
 int /*<<< orphan*/  ENTRY_ISVALID ; 
 int /*<<< orphan*/  ENTRY_TYPE ; 
 int bcma_erom_peek32 (struct bcma_erom*,scalar_t__*) ; 
 int bcma_erom_skip_core (struct bcma_erom*) ; 
 int bcma_erom_skip_mport (struct bcma_erom*) ; 
 int bcma_erom_skip_sport_region (struct bcma_erom*) ; 

__attribute__((used)) static int
bcma_erom_seek_next(struct bcma_erom *erom, uint8_t etype)
{
	uint32_t			entry;
	int				error;

	/* Iterate until we hit an entry matching the requested type. */
	while (!(error = bcma_erom_peek32(erom, &entry))) {
		/* Handle EOF */
		if (entry == BCMA_EROM_TABLE_EOF)
			return (ENOENT);

		/* Invalid entry */
		if (!BCMA_EROM_GET_ATTR(entry, ENTRY_ISVALID))
			return (EINVAL);

		/* Entry type matches? */
		if (BCMA_EROM_GET_ATTR(entry, ENTRY_TYPE) == etype)
			return (0);

		/* Skip non-matching entry types. */
		switch (BCMA_EROM_GET_ATTR(entry, ENTRY_TYPE)) {
		case BCMA_EROM_ENTRY_TYPE_CORE:
			if ((error = bcma_erom_skip_core(erom)))
				return (error);

			break;

		case BCMA_EROM_ENTRY_TYPE_MPORT:
			if ((error = bcma_erom_skip_mport(erom)))
				return (error);

			break;
		
		case BCMA_EROM_ENTRY_TYPE_REGION:
			if ((error = bcma_erom_skip_sport_region(erom)))
				return (error);
			break;

		default:
			/* Unknown entry type! */
			return (EINVAL);	
		}
	}

	return (error);
}