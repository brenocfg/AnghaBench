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
typedef  int /*<<< orphan*/  val ;
typedef  int uint64_t ;
typedef  int phandle_t ;
typedef  int cell_t ;

/* Variables and functions */
 int ENOENT ; 
 int OF_finddevice (char*) ; 
 int /*<<< orphan*/  OF_getencprop (int,char*,int*,int) ; 
 int /*<<< orphan*/  OF_hasprop (int,char*) ; 
 int PSL_DR ; 
 int PSL_EE ; 
 int PSL_IR ; 
 int PSL_SE ; 
 int mfmsr () ; 
 int opal_data ; 
 int opal_entrypoint ; 
 int opal_initialized ; 
 int opal_msr ; 

int
opal_check(void)
{
	phandle_t opal;
	cell_t val[2];

	if (opal_initialized)
		return (0);

	opal = OF_finddevice("/ibm,opal");
	if (opal == -1)
		return (ENOENT);

	if (!OF_hasprop(opal, "opal-base-address") ||
	    !OF_hasprop(opal, "opal-entry-address"))
		return (ENOENT);
	
	OF_getencprop(opal, "opal-base-address", val, sizeof(val));
	opal_data = ((uint64_t)val[0] << 32) | val[1];
	OF_getencprop(opal, "opal-entry-address", val, sizeof(val));
	opal_entrypoint = ((uint64_t)val[0] << 32) | val[1];

	opal_msr = mfmsr() & ~(PSL_EE | PSL_IR | PSL_DR | PSL_SE);

	opal_initialized = 1;

	return (0);
}