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
typedef  size_t u_int ;
struct uftdi_softc {int dummy; } ;
struct uftdi_param_config {size_t baud_lobits; scalar_t__ baud_hibits; } ;
typedef  int speed_t ;

/* Variables and functions */
 int ERANGE ; 
 size_t nitems (int const*) ; 

__attribute__((used)) static int
uftdi_sio_encode_baudrate(struct uftdi_softc *sc, speed_t speed,
	struct uftdi_param_config *cfg)
{
	u_int i;
	const speed_t sio_speeds[] = {
		300, 600, 1200, 2400, 4800, 9600, 19200, 38400, 57600, 115200
	};

	/*
	 * The original SIO chips were limited to a small choice of speeds
	 * listed in an internal table of speeds chosen by an index value.
	 */
	for (i = 0; i < nitems(sio_speeds); ++i) {
		if (speed == sio_speeds[i]) {
			cfg->baud_lobits = i;
			cfg->baud_hibits = 0;
			return (0);
		}
	}
	return (ERANGE);
}