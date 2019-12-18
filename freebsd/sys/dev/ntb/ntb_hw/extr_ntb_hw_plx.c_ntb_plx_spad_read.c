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
typedef  scalar_t__ u_int ;
struct ntb_plx_softc {unsigned int spad_count1; unsigned int spad_count2; int /*<<< orphan*/  conf_res; scalar_t__ spad_off2; scalar_t__ spad_off1; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  bus_read_4 (int /*<<< orphan*/ ,scalar_t__) ; 
 struct ntb_plx_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ntb_plx_spad_read(device_t dev, unsigned int idx, uint32_t *val)
{
	struct ntb_plx_softc *sc = device_get_softc(dev);
	u_int off;

	if (idx >= sc->spad_count1 + sc->spad_count2)
		return (EINVAL);

	if (idx < sc->spad_count1)
		off = sc->spad_off1 + idx * 4;
	else
		off = sc->spad_off2 + (idx - sc->spad_count1) * 4;
	*val = bus_read_4(sc->conf_res, off);
	return (0);
}