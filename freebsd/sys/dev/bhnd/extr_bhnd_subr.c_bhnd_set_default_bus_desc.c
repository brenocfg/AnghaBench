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
struct bhnd_chipid {int chip_type; int /*<<< orphan*/  chip_id; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  chip_name ;

/* Variables and functions */
 int BHND_CHIPID_MAX_NAMELEN ; 
#define  BHND_CHIPTYPE_BCMA 131 
#define  BHND_CHIPTYPE_BCMA_ALT 130 
#define  BHND_CHIPTYPE_SIBA 129 
#define  BHND_CHIPTYPE_UBUS 128 
 int /*<<< orphan*/  M_BHND ; 
 int /*<<< orphan*/  asprintf (char**,int /*<<< orphan*/ ,char*,char*,char const*) ; 
 int /*<<< orphan*/  bhnd_format_chip_id (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  device_set_desc_copy (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (char*,int /*<<< orphan*/ ) ; 

void
bhnd_set_default_bus_desc(device_t dev, const struct bhnd_chipid *chip_id)
{
	const char	*bus_name;
	char		*desc;
	char		 chip_name[BHND_CHIPID_MAX_NAMELEN];

	/* Determine chip type's bus name */
	switch (chip_id->chip_type) {
	case BHND_CHIPTYPE_SIBA:
		bus_name = "SIBA bus";
		break;
	case BHND_CHIPTYPE_BCMA:
	case BHND_CHIPTYPE_BCMA_ALT:
		bus_name = "BCMA bus";
		break;
	case BHND_CHIPTYPE_UBUS:
		bus_name = "UBUS bus";
		break;
	default:
		bus_name = "Unknown Type";
		break;
	}

	/* Format chip name */
	bhnd_format_chip_id(chip_name, sizeof(chip_name),
	     chip_id->chip_id);

	/* Format and set device description */
	asprintf(&desc, M_BHND, "%s %s", chip_name, bus_name);
	if (desc != NULL) {
		device_set_desc_copy(dev, desc);
		free(desc, M_BHND);
	} else {
		device_set_desc(dev, bus_name);
	}
	
}