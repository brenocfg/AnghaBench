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
struct uath_softc {int /*<<< orphan*/  sc_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  UATH_CMD_FLAG_MAGIC ; 
 int /*<<< orphan*/  WDCMSG_TARGET_GET_CAPABILITY ; 
 int /*<<< orphan*/  be32toh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htobe32 (int /*<<< orphan*/ ) ; 
 int uath_cmd_read (struct uath_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
uath_get_capability(struct uath_softc *sc, uint32_t cap, uint32_t *val)
{
	int error;

	cap = htobe32(cap);
	error = uath_cmd_read(sc, WDCMSG_TARGET_GET_CAPABILITY,
	    &cap, sizeof cap, val, sizeof(uint32_t), UATH_CMD_FLAG_MAGIC);
	if (error != 0) {
		device_printf(sc->sc_dev, "could not read capability %u\n",
		    be32toh(cap));
		return (error);
	}
	*val = be32toh(*val);
	return (error);
}