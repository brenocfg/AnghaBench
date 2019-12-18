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
struct mss_info {int conf_rid; int /*<<< orphan*/ * conf_base; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int OPL3SAx_DMACONF ; 
 int /*<<< orphan*/  OPL3SAx_MISC ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_IOPORT ; 
 int /*<<< orphan*/ * bus_alloc_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int conf_rd (struct mss_info*,int /*<<< orphan*/ ) ; 
 int port_rd (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  port_wr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static char *
ymf_test(device_t dev, struct mss_info *mss)
{
    	static int ports[] = {0x370, 0x310, 0x538};
    	int p, i, j, version;
    	static char *chipset[] = {
		NULL,			/* 0 */
		"OPL3-SA2 (YMF711)",	/* 1 */
		"OPL3-SA3 (YMF715)",	/* 2 */
		"OPL3-SA3 (YMF715)",	/* 3 */
		"OPL3-SAx (YMF719)",	/* 4 */
		"OPL3-SAx (YMF719)",	/* 5 */
		"OPL3-SAx (YMF719)",	/* 6 */
		"OPL3-SAx (YMF719)",	/* 7 */
    	};

    	for (p = 0; p < 3; p++) {
		mss->conf_rid = 1;
		mss->conf_base = bus_alloc_resource(dev,
					  	SYS_RES_IOPORT,
					  	&mss->conf_rid,
					  	ports[p], ports[p] + 1, 2,
					  	RF_ACTIVE);
		if (!mss->conf_base) return 0;

		/* Test the index port of the config registers */
		i = port_rd(mss->conf_base, 0);
		port_wr(mss->conf_base, 0, OPL3SAx_DMACONF);
		j = (port_rd(mss->conf_base, 0) == OPL3SAx_DMACONF)? 1 : 0;
		port_wr(mss->conf_base, 0, i);
		if (!j) {
	    		bus_release_resource(dev, SYS_RES_IOPORT,
			 		     mss->conf_rid, mss->conf_base);
	    		mss->conf_base = NULL;
	    		continue;
		}
		version = conf_rd(mss, OPL3SAx_MISC) & 0x07;
		return chipset[version];
    	}
    	return NULL;
}