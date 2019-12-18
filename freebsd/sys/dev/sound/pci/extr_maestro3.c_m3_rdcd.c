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
struct sc_info {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  kobj_t ;

/* Variables and functions */
 int /*<<< orphan*/  CODEC_COMMAND ; 
 int /*<<< orphan*/  CODEC_DATA ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int m3_rd_2 (struct sc_info*,int /*<<< orphan*/ ) ; 
 scalar_t__ m3_wait (struct sc_info*) ; 
 int /*<<< orphan*/  m3_wr_1 (struct sc_info*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
m3_rdcd(kobj_t kobj, void *devinfo, int regno)
{
	struct sc_info *sc = (struct sc_info *)devinfo;
	u_int32_t data;

	if (m3_wait(sc)) {
		device_printf(sc->dev, "m3_rdcd timed out.\n");
		return -1;
	}
	m3_wr_1(sc, CODEC_COMMAND, (regno & 0x7f) | 0x80);
	DELAY(50); /* ac97 cycle = 20.8 usec */
	if (m3_wait(sc)) {
		device_printf(sc->dev, "m3_rdcd timed out.\n");
		return -1;
	}
	data = m3_rd_2(sc, CODEC_DATA);
	return data;
}