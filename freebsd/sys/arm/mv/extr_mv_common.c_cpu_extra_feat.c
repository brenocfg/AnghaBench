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
typedef  int uint32_t ;

/* Variables and functions */
#define  MV_DEV_88F5182 134 
#define  MV_DEV_88F5281 133 
#define  MV_DEV_88F6281 132 
#define  MV_DEV_88F6282 131 
#define  MV_DEV_88RC8180 130 
#define  MV_DEV_MV78100 129 
#define  MV_DEV_MV78100_Z0 128 
 int /*<<< orphan*/  bootverbose ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  soc_id (int*,int*) ; 

uint32_t
cpu_extra_feat(void)
{
	uint32_t dev, rev;
	uint32_t ef = 0;

	soc_id(&dev, &rev);

	switch (dev) {
	case MV_DEV_88F6281:
	case MV_DEV_88F6282:
	case MV_DEV_88RC8180:
	case MV_DEV_MV78100_Z0:
	case MV_DEV_MV78100:
		__asm __volatile("mrc p15, 1, %0, c15, c1, 0" : "=r" (ef));
		break;
	case MV_DEV_88F5182:
	case MV_DEV_88F5281:
		__asm __volatile("mrc p15, 0, %0, c14, c0, 0" : "=r" (ef));
		break;
	default:
		if (bootverbose)
			printf("This ARM Core does not support any extra features\n");
	}

	return (ef);
}