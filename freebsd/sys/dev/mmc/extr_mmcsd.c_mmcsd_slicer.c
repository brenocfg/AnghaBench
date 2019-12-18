#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct mmcsd_softc {scalar_t__ enh_size; int /*<<< orphan*/  enh_base; struct mmcsd_part** part; } ;
struct mmcsd_part {TYPE_1__* disk; } ;
struct flash_slice {scalar_t__ size; int /*<<< orphan*/  label; int /*<<< orphan*/  base; } ;
typedef  int /*<<< orphan*/  name ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {char* d_name; int /*<<< orphan*/  d_unit; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ENXIO ; 
 size_t EXT_CSD_PART_CONFIG_ACC_DEFAULT ; 
 int /*<<< orphan*/  MMCSD_LABEL_ENH ; 
 int MMCSD_PART_NAMELEN ; 
 struct mmcsd_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char*,char const*) ; 

__attribute__((used)) static int
mmcsd_slicer(device_t dev, const char *provider,
    struct flash_slice *slices, int *nslices)
{
	char name[MMCSD_PART_NAMELEN];
	struct mmcsd_softc *sc;
	struct mmcsd_part *part;

	*nslices = 0;
	if (slices == NULL)
		return (ENOMEM);

	sc = device_get_softc(dev);
	if (sc->enh_size == 0)
		return (ENXIO);

	part = sc->part[EXT_CSD_PART_CONFIG_ACC_DEFAULT];
	snprintf(name, sizeof(name), "%s%d", part->disk->d_name,
	    part->disk->d_unit);
	if (strcmp(name, provider) != 0)
		return (ENXIO);

	*nslices = 1;
	slices[0].base = sc->enh_base;
	slices[0].size = sc->enh_size;
	slices[0].label = MMCSD_LABEL_ENH;
	return (0);
}