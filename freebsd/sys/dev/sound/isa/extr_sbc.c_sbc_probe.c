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
typedef  int u_int32_t ;
struct resource {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int ISA_PNP_PROBE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_IOPORT ; 
 struct resource* bus_alloc_resource_anywhere (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct resource*) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char*) ; 
 int isa_get_logicalid (int /*<<< orphan*/ ) ; 
 int isa_get_vendorid (int /*<<< orphan*/ ) ; 
 int sb_identify_board (struct resource*) ; 
 scalar_t__ sb_reset_dsp (struct resource*) ; 
 int /*<<< orphan*/  sbc_ids ; 

__attribute__((used)) static int
sbc_probe(device_t dev)
{
	char *s = NULL;
	u_int32_t lid, vid;

	lid = isa_get_logicalid(dev);
	vid = isa_get_vendorid(dev);
	if (lid) {
		if (lid == 0x01000000 && vid != 0x01009305) /* ALS0001 */
			return ENXIO;
		/* Check pnp ids */
		return ISA_PNP_PROBE(device_get_parent(dev), dev, sbc_ids);
	} else {
		int rid = 0, ver;
	    	struct resource *io;

		io = bus_alloc_resource_anywhere(dev, SYS_RES_IOPORT, &rid,
						 16, RF_ACTIVE);
		if (!io) goto bad;
    		if (sb_reset_dsp(io)) goto bad2;
		ver = sb_identify_board(io);
		if (ver == 0) goto bad2;
		switch ((ver & 0x00000f00) >> 8) {
		case 1:
			device_set_desc(dev, "SoundBlaster 1.0 (not supported)");
			s = NULL;
			break;

		case 2:
			s = "SoundBlaster 2.0";
			break;

		case 3:
			s = (ver & 0x0000f000)? "ESS 488" : "SoundBlaster Pro";
			break;

		case 4:
			s = "SoundBlaster 16";
			break;

		case 5:
			s = (ver & 0x00000008)? "ESS 688" : "ESS 1688";
			break;
	     	}
		if (s) device_set_desc(dev, s);
bad2:		bus_release_resource(dev, SYS_RES_IOPORT, rid, io);
bad:		return s? 0 : ENXIO;
	}
}