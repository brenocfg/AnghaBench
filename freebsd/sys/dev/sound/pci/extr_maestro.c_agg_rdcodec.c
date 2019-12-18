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
struct agg_info {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int AGG_RD (struct agg_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  AGG_WR (struct agg_info*,int /*<<< orphan*/ ,int,int) ; 
 int CODEC_CMD_READ ; 
 int /*<<< orphan*/  PORT_CODEC_CMD ; 
 int /*<<< orphan*/  PORT_CODEC_REG ; 
 scalar_t__ agg_codec_wait4idle (struct agg_info*) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
agg_rdcodec(struct agg_info *ess, int regno)
{
	int ret;

	/* We have to wait for a SAFE time to write addr/data */
	if (agg_codec_wait4idle(ess)) {
		/* Timed out. No read performed. */
		device_printf(ess->dev, "agg_rdcodec() PROGLESS timed out.\n");
		return -1;
	}

	AGG_WR(ess, PORT_CODEC_CMD, CODEC_CMD_READ | regno, 1);
	/*DELAY(21);	* AC97 cycle = 20.8usec */

	/* Wait for data retrieve */
	if (!agg_codec_wait4idle(ess)) {
		ret = AGG_RD(ess, PORT_CODEC_REG, 2);
	} else {
		/* Timed out. No read performed. */
		device_printf(ess->dev, "agg_rdcodec() RW_DONE timed out.\n");
		ret = -1;
	}

	return ret;
}