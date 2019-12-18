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
typedef  scalar_t__ uint32_t ;
struct bwn_softc {int /*<<< orphan*/  sc_dev; } ;
struct bwn_mac {struct bwn_softc* mac_sc; } ;

/* Variables and functions */
 int /*<<< orphan*/  BWN_LOCK (struct bwn_softc*) ; 
 int /*<<< orphan*/  BWN_MACCTL ; 
 scalar_t__ BWN_MACCTL_GMODE ; 
 scalar_t__ BWN_MACCTL_IHR_ON ; 
 int BWN_READ_2 (struct bwn_mac*,int /*<<< orphan*/ ) ; 
 scalar_t__ BWN_READ_4 (struct bwn_mac*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BWN_SHARED ; 
 int /*<<< orphan*/  BWN_TSF_CFP_START ; 
 int /*<<< orphan*/  BWN_TSF_CFP_START_HIGH ; 
 int /*<<< orphan*/  BWN_TSF_CFP_START_LOW ; 
 int /*<<< orphan*/  BWN_UNLOCK (struct bwn_softc*) ; 
 int /*<<< orphan*/  BWN_WRITE_2 (struct bwn_mac*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  BWN_WRITE_4 (struct bwn_mac*,int /*<<< orphan*/ ,int) ; 
 int ENODEV ; 
 scalar_t__ TESTVAL0 ; 
 scalar_t__ TESTVAL1 ; 
 int bhnd_get_hwrev (int /*<<< orphan*/ ) ; 
 scalar_t__ bwn_shm_read_4 (struct bwn_mac*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bwn_shm_write_4 (struct bwn_mac*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
bwn_chiptest(struct bwn_mac *mac)
{
#define	TESTVAL0	0x55aaaa55
#define	TESTVAL1	0xaa5555aa
	struct bwn_softc *sc = mac->mac_sc;
	uint32_t v, backup;

	BWN_LOCK(sc);

	backup = bwn_shm_read_4(mac, BWN_SHARED, 0);

	bwn_shm_write_4(mac, BWN_SHARED, 0, TESTVAL0);
	if (bwn_shm_read_4(mac, BWN_SHARED, 0) != TESTVAL0)
		goto error;
	bwn_shm_write_4(mac, BWN_SHARED, 0, TESTVAL1);
	if (bwn_shm_read_4(mac, BWN_SHARED, 0) != TESTVAL1)
		goto error;

	bwn_shm_write_4(mac, BWN_SHARED, 0, backup);

	if ((bhnd_get_hwrev(sc->sc_dev) >= 3) &&
	    (bhnd_get_hwrev(sc->sc_dev) <= 10)) {
		BWN_WRITE_2(mac, BWN_TSF_CFP_START, 0xaaaa);
		BWN_WRITE_4(mac, BWN_TSF_CFP_START, 0xccccbbbb);
		if (BWN_READ_2(mac, BWN_TSF_CFP_START_LOW) != 0xbbbb)
			goto error;
		if (BWN_READ_2(mac, BWN_TSF_CFP_START_HIGH) != 0xcccc)
			goto error;
	}
	BWN_WRITE_4(mac, BWN_TSF_CFP_START, 0);

	v = BWN_READ_4(mac, BWN_MACCTL) | BWN_MACCTL_GMODE;
	if (v != (BWN_MACCTL_GMODE | BWN_MACCTL_IHR_ON))
		goto error;

	BWN_UNLOCK(sc);
	return (0);
error:
	BWN_UNLOCK(sc);
	device_printf(sc->sc_dev, "failed to validate the chipaccess\n");
	return (ENODEV);
}