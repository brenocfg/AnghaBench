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
struct bhnd_erom_io {int dummy; } ;
struct bhnd_chipid {int chip_type; } ;
typedef  int /*<<< orphan*/  bhnd_erom_class_t ;

/* Variables and functions */
#define  BHND_CHIPTYPE_BCMA 130 
#define  BHND_CHIPTYPE_BCMA_ALT 129 
#define  BHND_CHIPTYPE_UBUS 128 
 int BUS_PROBE_DEFAULT ; 
 int BUS_PROBE_GENERIC ; 
 int EINVAL ; 
 int ENXIO ; 
 int bhnd_erom_read_chipid (struct bhnd_erom_io*,struct bhnd_chipid*) ; 

__attribute__((used)) static int
bcma_erom_probe(bhnd_erom_class_t *cls, struct bhnd_erom_io *eio,
    const struct bhnd_chipid *hint, struct bhnd_chipid *cid)
{
	int error;

	/* Hints aren't supported; all BCMA devices have a ChipCommon
	 * core */
	if (hint != NULL)
		return (EINVAL);

	/* Read and parse chip identification */
	if ((error = bhnd_erom_read_chipid(eio, cid)))
		return (error);

	/* Verify chip type */
	switch (cid->chip_type) {
		case BHND_CHIPTYPE_BCMA:
			return (BUS_PROBE_DEFAULT);

		case BHND_CHIPTYPE_BCMA_ALT:
		case BHND_CHIPTYPE_UBUS:
			return (BUS_PROBE_GENERIC);

		default:
			return (ENXIO);
	}	
}