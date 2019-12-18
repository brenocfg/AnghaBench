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
typedef  int U8 ;
typedef  int U32 ;

/* Variables and functions */

__attribute__((used)) static __inline U32
mpt_vol_pageaddr(U8 VolumeBus, U8 VolumeID)
{

	return (VolumeBus << 8 | VolumeID);
}