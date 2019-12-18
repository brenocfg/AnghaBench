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
struct ntb_plx_softc {scalar_t__ link; } ;
typedef  void* device_t ;

/* Variables and functions */
 int NTX_READ (struct ntb_plx_softc*,int) ; 
 int /*<<< orphan*/  NTX_WRITE (struct ntb_plx_softc*,int,int) ; 
 struct ntb_plx_softc* device_get_softc (void*) ; 
 int /*<<< orphan*/  device_printf (void*,char*) ; 
 int /*<<< orphan*/  ntb_db_event (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntb_link_event (void*) ; 
 int /*<<< orphan*/  ntb_plx_init (void*) ; 

__attribute__((used)) static void
ntb_plx_isr(void *arg)
{
	device_t dev = arg;
	struct ntb_plx_softc *sc = device_get_softc(dev);
	uint32_t val;

	ntb_db_event((device_t)arg, 0);

	if (sc->link)	/* Link Interface has no Link Error registers. */
		return;

	val = NTX_READ(sc, 0xfe0);
	if (val == 0)
		return;
	NTX_WRITE(sc, 0xfe0, val);
	if (val & 1)
		device_printf(dev, "Correctable Error\n");
	if (val & 2)
		device_printf(dev, "Uncorrectable Error\n");
	if (val & 4) {
		/* DL_Down resets link side registers, have to reinit. */
		ntb_plx_init(dev);
		ntb_link_event(dev);
	}
	if (val & 8)
		device_printf(dev, "Uncorrectable Error Message Drop\n");
}