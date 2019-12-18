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
 int PCICAR_BUSN ; 
 unsigned int PCICAR_DEVFNN ; 

__attribute__((used)) static unsigned long mcf_mk_pcicar(int bus, unsigned int devfn, int where)
{
	return (bus << PCICAR_BUSN) | (devfn << PCICAR_DEVFNN) | (where & 0xfc);
}