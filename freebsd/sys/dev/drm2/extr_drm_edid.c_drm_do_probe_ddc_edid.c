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
struct iic_msg {int slave; int len; unsigned char* buf; int /*<<< orphan*/  flags; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int DDC_ADDR ; 
 int DDC_SEGMENT_ADDR ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int,int) ; 
 int EDID_LENGTH ; 
 int /*<<< orphan*/  IIC_M_RD ; 
 int iicbus_transfer (int /*<<< orphan*/ ,struct iic_msg*,unsigned char) ; 

__attribute__((used)) static int
drm_do_probe_ddc_edid(device_t adapter, unsigned char *buf,
		      int block, int len)
{
	unsigned char start = block * EDID_LENGTH;
	unsigned char segment = block >> 1;
	unsigned char xfers = segment ? 3 : 2;
	int ret, retries = 5;

	/* The core i2c driver will automatically retry the transfer if the
	 * adapter reports EAGAIN. However, we find that bit-banging transfers
	 * are susceptible to errors under a heavily loaded machine and
	 * generate spurious NAKs and timeouts. Retrying the transfer
	 * of the individual block a few times seems to overcome this.
	 */
	do {
		struct iic_msg msgs[] = {
			{
				.slave	= DDC_SEGMENT_ADDR << 1,
				.flags	= 0,
				.len	= 1,
				.buf	= &segment,
			}, {
				.slave	= DDC_ADDR << 1,
				.flags	= 0,
				.len	= 1,
				.buf	= &start,
			}, {
				.slave	= DDC_ADDR << 1,
				.flags	= IIC_M_RD,
				.len	= len,
				.buf	= buf,
			}
		};

	/*
	 * Avoid sending the segment addr to not upset non-compliant ddc
	 * monitors.
	 */
		ret = iicbus_transfer(adapter, &msgs[3 - xfers], xfers);

		if (ret != 0)
			DRM_DEBUG_KMS("iicbus_transfer countdown %d error %d\n",
			    retries, ret);
	} while (ret != 0 && --retries);

	return ret == 0 ? 0 : -1;
}