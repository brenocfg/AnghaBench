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
struct macio_reg {scalar_t__ mr_base; scalar_t__ mr_size; } ;
struct macio_devinfo {int /*<<< orphan*/  mdi_resources; } ;
typedef  scalar_t__ phandle_t ;
typedef  int /*<<< orphan*/  layout_id ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 scalar_t__ OF_child (scalar_t__) ; 
 int OF_getprop (scalar_t__,char*,...) ; 
 int OF_getprop_alloc_multi (scalar_t__,char*,int,void**) ; 
 scalar_t__ OF_parent (scalar_t__) ; 
 scalar_t__ OF_peer (scalar_t__) ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  resource_list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static void
macio_add_reg(phandle_t devnode, struct macio_devinfo *dinfo)
{
	struct		macio_reg *reg, *regp;
	phandle_t 	child;
	char		buf[8];
	int		i, layout_id = 0, nreg, res;

	nreg = OF_getprop_alloc_multi(devnode, "reg", sizeof(*reg), (void **)&reg);
	if (nreg == -1)
		return;

        /*
         *  Some G5's have broken properties in the i2s-a area. If so we try
         *  to fix it. Right now we know of two different cases, one for
         *  sound layout-id 36 and the other one for sound layout-id 76.
         *  What is missing is the base address for the memory addresses.
         *  We take them from the parent node (i2s) and use the size
         *  information from the child. 
         */

        if (reg[0].mr_base == 0) {
		child = OF_child(devnode);
		while (child != 0) {
			res = OF_getprop(child, "name", buf, sizeof(buf));
			if (res > 0 && strcmp(buf, "sound") == 0)
				break;
			child = OF_peer(child);
		}

                res = OF_getprop(child, "layout-id", &layout_id,
				sizeof(layout_id));

                if (res > 0 && (layout_id == 36 || layout_id == 76)) {
                        res = OF_getprop_alloc_multi(OF_parent(devnode), "reg",
						sizeof(*regp), (void **)&regp);
                        reg[0] = regp[0];
                        reg[1].mr_base = regp[1].mr_base;
                        reg[2].mr_base = regp[1].mr_base + reg[1].mr_size;
                }
        } 

	for (i = 0; i < nreg; i++) {
		resource_list_add(&dinfo->mdi_resources, SYS_RES_MEMORY, i,
		    reg[i].mr_base, reg[i].mr_base + reg[i].mr_size,
		    reg[i].mr_size);
	}
}