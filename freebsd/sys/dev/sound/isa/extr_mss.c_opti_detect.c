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
struct mss_info {int conf_rid; int indir_rid; int optibase; int password; int passwdreg; int bd_id; int /*<<< orphan*/ * conf_base; int /*<<< orphan*/ * indir; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
#define  MD_OPTI924 129 
#define  MD_OPTI930 128 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_IOPORT ; 
 void* bus_alloc_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int opti_read (struct mss_info*,int) ; 

__attribute__((used)) static int
opti_detect(device_t dev, struct mss_info *mss)
{
	int c;
	static const struct opticard {
		int boardid;
		int passwdreg;
		int password;
		int base;
		int indir_reg;
	} cards[] = {
		{ MD_OPTI930, 0, 0xe4, 0xf8f, 0xe0e },	/* 930 */
		{ MD_OPTI924, 3, 0xe5, 0xf8c, 0,    },	/* 924 */
		{ 0 },
	};
	mss->conf_rid = 3;
	mss->indir_rid = 4;
	for (c = 0; cards[c].base; c++) {
		mss->optibase = cards[c].base;
		mss->password = cards[c].password;
		mss->passwdreg = cards[c].passwdreg;
		mss->bd_id = cards[c].boardid;

		if (cards[c].indir_reg)
			mss->indir = bus_alloc_resource(dev, SYS_RES_IOPORT,
				&mss->indir_rid, cards[c].indir_reg,
				cards[c].indir_reg+1, 1, RF_ACTIVE);

		mss->conf_base = bus_alloc_resource(dev, SYS_RES_IOPORT,
			&mss->conf_rid, mss->optibase, mss->optibase+9,
			9, RF_ACTIVE);

		if (opti_read(mss, 1) != 0xff) {
			return 1;
		} else {
			if (mss->indir)
				bus_release_resource(dev, SYS_RES_IOPORT, mss->indir_rid, mss->indir);
			mss->indir = NULL;
			if (mss->conf_base)
				bus_release_resource(dev, SYS_RES_IOPORT, mss->conf_rid, mss->conf_base);
			mss->conf_base = NULL;
		}
	}
	return 0;
}