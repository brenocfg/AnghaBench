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

/* Variables and functions */
 int nd_smi_module_loaded ; 
 scalar_t__ smiLoadModule (char const*) ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,char const*) ; 

int
nd_load_smi_module(const char *module, char *errbuf, size_t errbuf_size)
{
#ifdef USE_LIBSMI
	if (smiLoadModule(module) == 0) {
		snprintf(errbuf, errbuf_size, "could not load MIB module %s",
		    module);
		return (-1);
	}
	nd_smi_module_loaded = 1;
	return (0);
#else
	snprintf(errbuf, errbuf_size, "MIB module %s not loaded: no libsmi support",
	    module);
	return (-1);
#endif
}