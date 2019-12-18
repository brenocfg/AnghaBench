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
struct an_softc {int /*<<< orphan*/  an_mtx; int /*<<< orphan*/  an_dev; scalar_t__ mpi350; int /*<<< orphan*/  port_res; } ;
struct an_ltv_ssidlist_new {int an_len; TYPE_1__* an_entry; int /*<<< orphan*/  an_type; } ;
struct an_ltv_gen {int dummy; } ;
typedef  int /*<<< orphan*/  ssid ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {int /*<<< orphan*/  an_ssid; } ;

/* Variables and functions */
 int /*<<< orphan*/  AN_CMD_READCFG ; 
 int /*<<< orphan*/  AN_DEF_SSID ; 
 int /*<<< orphan*/  AN_EVENT_ACK (scalar_t__) ; 
 int /*<<< orphan*/  AN_INT_EN (scalar_t__) ; 
 int AN_IOSIZ ; 
 int /*<<< orphan*/  AN_LOCK (struct an_softc*) ; 
 int /*<<< orphan*/  AN_RID_SSIDLIST ; 
 int /*<<< orphan*/  AN_UNLOCK (struct an_softc*) ; 
 int /*<<< orphan*/  CSR_WRITE_2 (struct an_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  MTX_NETWORK_LOCK ; 
 int an_alloc_port (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ an_cmd (struct an_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ an_read_record (struct an_softc*,struct an_ltv_gen*) ; 
 int /*<<< orphan*/  an_reset (struct an_softc*) ; 
 int /*<<< orphan*/  bzero (char*,int) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 struct an_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rman_get_start (int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
an_probe(device_t dev)
{
	struct an_softc *sc = device_get_softc(dev);
	struct an_ltv_ssidlist_new	ssid;
	int	error;

	bzero((char *)&ssid, sizeof(ssid));

	error = an_alloc_port(dev, 0, AN_IOSIZ);
	if (error != 0)
		return (0);

	/* can't do autoprobing */
	if (rman_get_start(sc->port_res) == -1)
		return(0);

	/*
	 * We need to fake up a softc structure long enough
	 * to be able to issue commands and call some of the
	 * other routines.
	 */
	ssid.an_len = sizeof(ssid);
	ssid.an_type = AN_RID_SSIDLIST;

	/* Make sure interrupts are disabled. */
	sc->mpi350 = 0;
	CSR_WRITE_2(sc, AN_INT_EN(sc->mpi350), 0);
	CSR_WRITE_2(sc, AN_EVENT_ACK(sc->mpi350), 0xFFFF);

	sc->an_dev = dev;
	mtx_init(&sc->an_mtx, device_get_nameunit(dev), MTX_NETWORK_LOCK,
	    MTX_DEF);
	AN_LOCK(sc);
	an_reset(sc);

	if (an_cmd(sc, AN_CMD_READCFG, 0)) {
		AN_UNLOCK(sc);
		goto fail;
	}

	if (an_read_record(sc, (struct an_ltv_gen *)&ssid)) {
		AN_UNLOCK(sc);
		goto fail;
	}

	/* See if the ssid matches what we expect ... but doesn't have to */
	if (strcmp(ssid.an_entry[0].an_ssid, AN_DEF_SSID)) {
		AN_UNLOCK(sc);
		goto fail;
	}

	AN_UNLOCK(sc);
	return(AN_IOSIZ);
fail:
	mtx_destroy(&sc->an_mtx);
	return(0);
}