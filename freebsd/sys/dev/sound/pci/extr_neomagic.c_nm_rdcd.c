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
struct sc_info {int /*<<< orphan*/  dev; scalar_t__ ac97_base; } ;
typedef  int /*<<< orphan*/  kobj_t ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int nm_rd (struct sc_info*,scalar_t__,int) ; 
 int /*<<< orphan*/  nm_waitcd (struct sc_info*) ; 

__attribute__((used)) static int
nm_rdcd(kobj_t obj, void *devinfo, int regno)
{
	struct sc_info *sc = (struct sc_info *)devinfo;
	u_int32_t x;

	if (!nm_waitcd(sc)) {
		x = nm_rd(sc, sc->ac97_base + regno, 2);
		DELAY(1000);
		return x;
	} else {
		device_printf(sc->dev, "ac97 codec not ready\n");
		return -1;
	}
}