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
struct uath_write_mac {int /*<<< orphan*/  data; void* len; void* reg; } ;
struct uath_softc {int /*<<< orphan*/  sc_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  WDCMSG_TARGET_SET_CONFIG ; 
 int /*<<< orphan*/  bcopy (void const*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int,int) ; 
 void* htobe32 (int) ; 
 int uath_cmd_write (struct uath_softc*,int /*<<< orphan*/ ,struct uath_write_mac*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
uath_config_multi(struct uath_softc *sc, uint32_t reg, const void *data,
    int len)
{
	struct uath_write_mac write;
	int error;

	write.reg = htobe32(reg);
	write.len = htobe32(len);
	bcopy(data, write.data, len);

	/* properly handle the case where len is zero (reset) */
	error = uath_cmd_write(sc, WDCMSG_TARGET_SET_CONFIG, &write,
	    (len == 0) ? sizeof (uint32_t) : 2 * sizeof (uint32_t) + len, 0);
	if (error != 0) {
		device_printf(sc->sc_dev,
		    "could not write %d bytes to register 0x%02x\n", len, reg);
	}
	return (error);
}