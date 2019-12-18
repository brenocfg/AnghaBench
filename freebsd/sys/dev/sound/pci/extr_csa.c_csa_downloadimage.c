#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u_long ;
typedef  int /*<<< orphan*/  csa_res ;
struct TYPE_4__ {size_t BA1Array; TYPE_1__* MemoryStat; } ;
struct TYPE_3__ {int ulSourceSize; int /*<<< orphan*/  ulDestAddr; } ;

/* Variables and functions */
 size_t INKY_MEMORY_COUNT ; 
 TYPE_2__ cs461x_firmware ; 
 int csa_transferimage (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
csa_downloadimage(csa_res *resp)
{
	int ret;
	u_long ul, offset;

	for (ul = 0, offset = 0 ; ul < INKY_MEMORY_COUNT ; ul++) {
	        /*
	         * DMA this block from host memory to the appropriate
	         * memory on the CSDevice.
	         */
		ret = csa_transferimage(resp,
		    cs461x_firmware.BA1Array + offset,
		    cs461x_firmware.MemoryStat[ul].ulDestAddr,
		    cs461x_firmware.MemoryStat[ul].ulSourceSize);
		if (ret)
			return (ret);
		offset += cs461x_firmware.MemoryStat[ul].ulSourceSize >> 2;
	}
	return (0);
}