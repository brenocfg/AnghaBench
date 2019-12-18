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
typedef  int u32 ;
typedef  int u16 ;
struct TYPE_2__ {int /*<<< orphan*/  IRVolumeMappingFlags; int /*<<< orphan*/  Flags; } ;
struct mps_softc {int max_devices; int max_volumes; TYPE_1__ ioc_pg8; } ;

/* Variables and functions */
 int MPI2_IOCPAGE8_FLAGS_RESERVED_TARGETID_0 ; 
 int MPI2_IOCPAGE8_IRFLAGS_LOW_VOLUME_MAPPING ; 
 int MPI2_IOCPAGE8_IRFLAGS_MASK_VOLUME_MAPPING_MODE ; 
 int le16toh (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
_mapping_get_ir_maprange(struct mps_softc *sc, u32 *start_idx, u32 *end_idx)
{
	u16 volume_mapping_flags;
	u16 ioc_pg8_flags = le16toh(sc->ioc_pg8.Flags);

	volume_mapping_flags = le16toh(sc->ioc_pg8.IRVolumeMappingFlags) &
	    MPI2_IOCPAGE8_IRFLAGS_MASK_VOLUME_MAPPING_MODE;
	if (volume_mapping_flags == MPI2_IOCPAGE8_IRFLAGS_LOW_VOLUME_MAPPING) {
		*start_idx = 0;
		if (ioc_pg8_flags & MPI2_IOCPAGE8_FLAGS_RESERVED_TARGETID_0)
			*start_idx = 1;
	} else
		*start_idx = sc->max_devices - sc->max_volumes;
	*end_idx = *start_idx + sc->max_volumes - 1;
}