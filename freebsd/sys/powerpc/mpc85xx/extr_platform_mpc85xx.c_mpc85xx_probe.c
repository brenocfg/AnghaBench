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
typedef  int u_int ;
typedef  int /*<<< orphan*/  platform_t ;

/* Variables and functions */
 int BUS_PROBE_DEFAULT ; 
 int ENXIO ; 
#define  FSL_E500mc 132 
#define  FSL_E500v1 131 
#define  FSL_E500v2 130 
#define  FSL_E5500 129 
#define  FSL_E6500 128 
 int mfpvr () ; 

__attribute__((used)) static int
mpc85xx_probe(platform_t plat)
{
	u_int pvr = (mfpvr() >> 16) & 0xFFFF;

	switch (pvr) {
		case FSL_E500v1:
		case FSL_E500v2:
		case FSL_E500mc:
		case FSL_E5500:
		case FSL_E6500:
			return (BUS_PROBE_DEFAULT);
	}
	return (ENXIO);
}