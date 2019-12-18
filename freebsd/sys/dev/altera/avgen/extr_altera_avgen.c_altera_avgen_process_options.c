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
struct altera_avgen_softc {int avg_width; scalar_t__ avg_flags; int /*<<< orphan*/  avg_dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
#define  ALTERA_AVALON_CHAR_EXEC 130 
#define  ALTERA_AVALON_CHAR_READ 129 
#define  ALTERA_AVALON_CHAR_WRITE 128 
 scalar_t__ ALTERA_AVALON_FLAG_GEOM_READ ; 
 scalar_t__ ALTERA_AVALON_FLAG_GEOM_WRITE ; 
 scalar_t__ ALTERA_AVALON_FLAG_MMAP_EXEC ; 
 scalar_t__ ALTERA_AVALON_FLAG_MMAP_READ ; 
 scalar_t__ ALTERA_AVALON_FLAG_MMAP_WRITE ; 
 scalar_t__ ALTERA_AVALON_FLAG_READ ; 
 scalar_t__ ALTERA_AVALON_FLAG_WRITE ; 
 char const ALTERA_AVALON_STR_DEVNAME ; 
 int /*<<< orphan*/  ALTERA_AVALON_STR_DEVUNIT ; 
 int /*<<< orphan*/  ALTERA_AVALON_STR_FILEIO ; 
 int /*<<< orphan*/  ALTERA_AVALON_STR_GEOMIO ; 
 int /*<<< orphan*/  ALTERA_AVALON_STR_MMAPIO ; 
 int /*<<< orphan*/  ALTERA_AVALON_STR_WIDTH ; 
 int ENXIO ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char const,...) ; 

__attribute__((used)) static int
altera_avgen_process_options(struct altera_avgen_softc *sc,
    const char *str_fileio, const char *str_geomio, const char *str_mmapio,
    const char *str_devname, int devunit)
{
	const char *cp;
	device_t dev = sc->avg_dev;

	/*
	 * Check for valid combinations of options.
	 */
	if (str_fileio == NULL && str_geomio == NULL && str_mmapio == NULL) {
		device_printf(dev,
		    "at least one of %s, %s, or %s must be specified\n",
		    ALTERA_AVALON_STR_FILEIO, ALTERA_AVALON_STR_GEOMIO,
		    ALTERA_AVALON_STR_MMAPIO);
		return (ENXIO);
	}

	/*
	 * Validity check: a device can either be a GEOM device (in which case
	 * we use GEOM to register the device node), or a special device --
	 * but not both as that causes a collision in /dev.
	 */
	if (str_geomio != NULL && (str_fileio != NULL || str_mmapio != NULL)) {
		device_printf(dev,
		    "at most one of %s and (%s or %s) may be specified\n",
		    ALTERA_AVALON_STR_GEOMIO, ALTERA_AVALON_STR_FILEIO,
		    ALTERA_AVALON_STR_MMAPIO);
		return (ENXIO);
	}

	/*
	 * Ensure that a unit is specified if a name is also specified.
	 */
	if (str_devname == NULL && devunit != -1) {
		device_printf(dev, "%s requires %s be specified\n",
		    ALTERA_AVALON_STR_DEVUNIT, ALTERA_AVALON_STR_DEVNAME);
		return (ENXIO);
	}

	/*
	 * Extract, digest, and save values.
	 */
	switch (sc->avg_width) {
	case 1:
	case 2:
	case 4:
#ifdef NOTYET
	case 8:
#endif
		break;

	default:
		device_printf(dev, "%s unsupported value %u\n",
		    ALTERA_AVALON_STR_WIDTH, sc->avg_width);
		return (ENXIO);
	}
	sc->avg_flags = 0;
	if (str_fileio != NULL) {
		for (cp = str_fileio; *cp != '\0'; cp++) {
			switch (*cp) {
			case ALTERA_AVALON_CHAR_READ:
				sc->avg_flags |= ALTERA_AVALON_FLAG_READ;
				break;

			case ALTERA_AVALON_CHAR_WRITE:
				sc->avg_flags |= ALTERA_AVALON_FLAG_WRITE;
				break;

			default:
				device_printf(dev,
				    "invalid %s character %c\n", 
				    ALTERA_AVALON_STR_FILEIO, *cp);
				return (ENXIO);
			}
		}
	}
	if (str_geomio != NULL) {
		for (cp = str_geomio; *cp != '\0'; cp++){
			switch (*cp) {
			case ALTERA_AVALON_CHAR_READ:
				sc->avg_flags |= ALTERA_AVALON_FLAG_GEOM_READ;
				break;

			case ALTERA_AVALON_CHAR_WRITE:
				sc->avg_flags |= ALTERA_AVALON_FLAG_GEOM_WRITE;
				break;

			default:
				device_printf(dev,
				    "invalid %s character %c\n",
				    ALTERA_AVALON_STR_GEOMIO, *cp);
				return (ENXIO);
			}
		}
	}
	if (str_mmapio != NULL) {
		for (cp = str_mmapio; *cp != '\0'; cp++) {
			switch (*cp) {
			case ALTERA_AVALON_CHAR_READ:
				sc->avg_flags |= ALTERA_AVALON_FLAG_MMAP_READ;
				break;

			case ALTERA_AVALON_CHAR_WRITE:
				sc->avg_flags |=
				    ALTERA_AVALON_FLAG_MMAP_WRITE;
				break;

			case ALTERA_AVALON_CHAR_EXEC:
				sc->avg_flags |= ALTERA_AVALON_FLAG_MMAP_EXEC;
				break;

			default:
				device_printf(dev,
				    "invalid %s character %c\n",
				    ALTERA_AVALON_STR_MMAPIO, *cp);
				return (ENXIO);
			}
		}
	}
	return (0);
}