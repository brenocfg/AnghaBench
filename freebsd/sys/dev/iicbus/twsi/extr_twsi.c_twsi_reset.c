#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  u_int ;
typedef  size_t u_char ;
struct twsi_softc {int /*<<< orphan*/  mutex; int /*<<< orphan*/  reg_control; int /*<<< orphan*/  reg_baud_rate; int /*<<< orphan*/  reg_soft_reset; TYPE_1__* baud_rate; int /*<<< orphan*/  iicbus; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {int param; } ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  IICBUS_GET_FREQUENCY (int /*<<< orphan*/ ,size_t) ; 
#define  IIC_FAST 131 
#define  IIC_FASTEST 130 
#define  IIC_SLOW 129 
#define  IIC_UNKNOWN 128 
 int TWSI_CONTROL_TWSIEN ; 
 int /*<<< orphan*/  TWSI_WRITE (struct twsi_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  debugf (int /*<<< orphan*/ ,char*,int) ; 
 struct twsi_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int twsi_calc_baud_rate (struct twsi_softc*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int
twsi_reset(device_t dev, u_char speed, u_char addr, u_char *oldaddr)
{
	struct twsi_softc *sc;
	uint32_t param;
#ifdef EXT_RESOURCES
	u_int busfreq;
#endif

	sc = device_get_softc(dev);

#ifdef EXT_RESOURCES
	busfreq = IICBUS_GET_FREQUENCY(sc->iicbus, speed);

	if (twsi_calc_baud_rate(sc, busfreq, &param) == -1) {
#endif
		switch (speed) {
		case IIC_SLOW:
		case IIC_FAST:
			param = sc->baud_rate[speed].param;
			debugf(dev, "Using IIC_FAST mode with speed param=%x\n", param);
			break;
		case IIC_FASTEST:
		case IIC_UNKNOWN:
		default:
			param = sc->baud_rate[IIC_FAST].param;
			debugf(dev, "Using IIC_FASTEST/UNKNOWN mode with speed param=%x\n", param);
			break;
		}
#ifdef EXT_RESOURCES
	}
#endif

	debugf(dev, "Using clock param=%x\n", param);

	mtx_lock(&sc->mutex);
	TWSI_WRITE(sc, sc->reg_soft_reset, 0x0);
	TWSI_WRITE(sc, sc->reg_baud_rate, param);
	TWSI_WRITE(sc, sc->reg_control, TWSI_CONTROL_TWSIEN);
	DELAY(1000);
	mtx_unlock(&sc->mutex);

	return (0);
}