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
typedef  int /*<<< orphan*/  uint32_t ;
struct a10hdmi_softc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  HDMI_READ (struct a10hdmi_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HDMI_VID_CTRL ; 
 int /*<<< orphan*/  HDMI_WRITE (struct a10hdmi_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VID_CTRL_VIDEO_EN ; 
 struct a10hdmi_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
a10hdmi_enable(device_t dev, int onoff)
{
	struct a10hdmi_softc *sc;
	uint32_t val;

	sc = device_get_softc(dev);

	/* Enable or disable video output */
	val = HDMI_READ(sc, HDMI_VID_CTRL);
	if (onoff)
		val |= VID_CTRL_VIDEO_EN;
	else
		val &= ~VID_CTRL_VIDEO_EN;
	HDMI_WRITE(sc, HDMI_VID_CTRL, val);

	return (0);
}