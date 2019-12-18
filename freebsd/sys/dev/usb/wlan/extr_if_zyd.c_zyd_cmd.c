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
typedef  int /*<<< orphan*/  uint16_t ;
struct zyd_softc {int /*<<< orphan*/  sc_rqh; int /*<<< orphan*/  sc_dev; int /*<<< orphan*/  sc_mtx; int /*<<< orphan*/ * sc_xfer; } ;
struct zyd_rq {int ilen; int olen; int flags; void* odata; void const* idata; struct zyd_cmd* cmd; } ;
struct zyd_cmd {int /*<<< orphan*/  data; int /*<<< orphan*/  code; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (struct zyd_softc*,int /*<<< orphan*/ ,char*,struct zyd_rq*,int,...) ; 
 int EINVAL ; 
 int /*<<< orphan*/  STAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct zyd_rq*,struct zyd_rq) ; 
 int /*<<< orphan*/  STAILQ_REMOVE (int /*<<< orphan*/ *,struct zyd_rq*,int /*<<< orphan*/ ,struct zyd_rq) ; 
 int /*<<< orphan*/  ZYD_DEBUG_CMD ; 
 size_t ZYD_INTR_RD ; 
 size_t ZYD_INTR_WR ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  htole16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hz ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void const*,int) ; 
 int mtx_sleep (struct zyd_rq*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_transfer_start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zyd_rq ; 

__attribute__((used)) static int
zyd_cmd(struct zyd_softc *sc, uint16_t code, const void *idata, int ilen,
    void *odata, int olen, int flags)
{
	struct zyd_cmd cmd;
	struct zyd_rq rq;
	int error;

	if (ilen > (int)sizeof(cmd.data))
		return (EINVAL);

	cmd.code = htole16(code);
	memcpy(cmd.data, idata, ilen);
	DPRINTF(sc, ZYD_DEBUG_CMD, "sending cmd %p = %*D\n",
	    &rq, ilen, idata, ":");

	rq.cmd = &cmd;
	rq.idata = idata;
	rq.odata = odata;
	rq.ilen = sizeof(uint16_t) + ilen;
	rq.olen = olen;
	rq.flags = flags;
	STAILQ_INSERT_TAIL(&sc->sc_rqh, &rq, rq);
	usbd_transfer_start(sc->sc_xfer[ZYD_INTR_RD]);
	usbd_transfer_start(sc->sc_xfer[ZYD_INTR_WR]);

	/* wait at most one second for command reply */
	error = mtx_sleep(&rq, &sc->sc_mtx, 0 , "zydcmd", hz);
	if (error)
		device_printf(sc->sc_dev, "command timeout\n");
	STAILQ_REMOVE(&sc->sc_rqh, &rq, zyd_rq, rq);
	DPRINTF(sc, ZYD_DEBUG_CMD, "finsihed cmd %p, error = %d \n",
	    &rq, error);

	return (error);
}