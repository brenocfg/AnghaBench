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
typedef  int u_int32_t ;
struct agg_info {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  AGG_WR (struct agg_info*,int /*<<< orphan*/ ,int,int) ; 
 int CODEC_CMD_WRITE ; 
 int /*<<< orphan*/  PORT_CODEC_CMD ; 
 int /*<<< orphan*/  PORT_CODEC_REG ; 
 scalar_t__ agg_codec_wait4idle (struct agg_info*) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
agg_wrcodec(struct agg_info *ess, int regno, u_int32_t data)
{
	/* We have to wait for a SAFE time to write addr/data */
	if (agg_codec_wait4idle(ess)) {
		/* Timed out. Abort writing. */
		device_printf(ess->dev, "agg_wrcodec() PROGLESS timed out.\n");
		return -1;
	}

	AGG_WR(ess, PORT_CODEC_REG, data, 2);
	AGG_WR(ess, PORT_CODEC_CMD, CODEC_CMD_WRITE | regno, 1);

	/* Wait for write completion */
	if (agg_codec_wait4idle(ess)) {
		/* Timed out. */
		device_printf(ess->dev, "agg_wrcodec() RW_DONE timed out.\n");
		return -1;
	}

	return 0;
}