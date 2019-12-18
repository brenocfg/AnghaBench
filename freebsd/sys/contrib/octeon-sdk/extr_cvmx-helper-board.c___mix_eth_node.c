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
typedef  int /*<<< orphan*/  name_buffer ;

/* Variables and functions */
 int /*<<< orphan*/  cvmx_dprintf (char*,...) ; 
 char* fdt_getprop (void const*,int,char*,int /*<<< orphan*/ *) ; 
 int fdt_path_offset (void const*,char const*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static int __mix_eth_node(const void *fdt_addr, int aliases, int interface_index)
{
    char name_buffer[20];
    const char*mix_path;
    int mix;

#ifdef __U_BOOT__
    sprintf(name_buffer, "mix%d", interface_index);
#else
    snprintf(name_buffer, sizeof(name_buffer), "mix%d", interface_index);
#endif
    mix_path = fdt_getprop(fdt_addr, aliases, name_buffer, NULL);
    if (!mix_path)
    {
        cvmx_dprintf("ERROR: mix%d path not found in device tree\n",interface_index);
    }
    mix = fdt_path_offset(fdt_addr, mix_path);
    if (mix < 0)
    {
        cvmx_dprintf("ERROR: %s not found in device tree\n", mix_path);
        return -1;
    }
    return mix;
}