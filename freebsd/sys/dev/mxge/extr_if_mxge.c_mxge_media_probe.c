#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint32_t ;
struct mxge_media_type {int bitmask; int name; scalar_t__ flag; } ;
struct TYPE_8__ {scalar_t__ connector; scalar_t__ current_media; int /*<<< orphan*/  dev; scalar_t__ need_media_probe; } ;
typedef  TYPE_1__ mxge_softc_t ;
struct TYPE_9__ {int data0; void* data1; } ;
typedef  TYPE_2__ mxge_cmd_t ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int EBUSY ; 
 int MXGEFW_CMD_ERROR_I2C_ABSENT ; 
 int MXGEFW_CMD_ERROR_I2C_FAILURE ; 
 int /*<<< orphan*/  MXGEFW_CMD_I2C_BYTE ; 
 int /*<<< orphan*/  MXGEFW_CMD_I2C_READ ; 
 int MXGEFW_CMD_OK ; 
 scalar_t__ MXGE_SFP ; 
 scalar_t__ MXGE_XFP ; 
 void* MXGE_XFP_COMPLIANCE_BYTE ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  mxge_media_init (TYPE_1__*) ; 
 int /*<<< orphan*/  mxge_media_set (TYPE_1__*,scalar_t__) ; 
 int mxge_send_cmd (TYPE_1__*,int /*<<< orphan*/ ,TYPE_2__*) ; 
 struct mxge_media_type* mxge_sfp_media_types ; 
 scalar_t__ mxge_verbose ; 
 struct mxge_media_type* mxge_xfp_media_types ; 
 int nitems (struct mxge_media_type*) ; 

__attribute__((used)) static void
mxge_media_probe(mxge_softc_t *sc)
{
	mxge_cmd_t cmd;
	char *cage_type;

	struct mxge_media_type *mxge_media_types = NULL;
	int i, err, ms, mxge_media_type_entries;
	uint32_t byte;

	sc->need_media_probe = 0;

	if (sc->connector == MXGE_XFP) {
		/* -R is XFP */
		mxge_media_types = mxge_xfp_media_types;
		mxge_media_type_entries =
			nitems(mxge_xfp_media_types);
		byte = MXGE_XFP_COMPLIANCE_BYTE;
		cage_type = "XFP";
	} else 	if (sc->connector == MXGE_SFP) {
		/* -S or -2S is SFP+ */
		mxge_media_types = mxge_sfp_media_types;
		mxge_media_type_entries =
			nitems(mxge_sfp_media_types);
		cage_type = "SFP+";
		byte = 3;
	} else {
		/* nothing to do; media type cannot change */
		return;
	}

	/*
	 * At this point we know the NIC has an XFP cage, so now we
	 * try to determine what is in the cage by using the
	 * firmware's XFP I2C commands to read the XFP 10GbE compilance
	 * register.  We read just one byte, which may take over
	 * a millisecond
	 */

	cmd.data0 = 0;	 /* just fetch 1 byte, not all 256 */
	cmd.data1 = byte;
	err = mxge_send_cmd(sc, MXGEFW_CMD_I2C_READ, &cmd);
	if (err == MXGEFW_CMD_ERROR_I2C_FAILURE) {
		device_printf(sc->dev, "failed to read XFP\n");
	}
	if (err == MXGEFW_CMD_ERROR_I2C_ABSENT) {
		device_printf(sc->dev, "Type R/S with no XFP!?!?\n");
	}
	if (err != MXGEFW_CMD_OK) {
		return;
	}

	/* now we wait for the data to be cached */
	cmd.data0 = byte;
	err = mxge_send_cmd(sc, MXGEFW_CMD_I2C_BYTE, &cmd);
	for (ms = 0; (err == EBUSY) && (ms < 50); ms++) {
		DELAY(1000);
		cmd.data0 = byte;
		err = mxge_send_cmd(sc, MXGEFW_CMD_I2C_BYTE, &cmd);
	}
	if (err != MXGEFW_CMD_OK) {
		device_printf(sc->dev, "failed to read %s (%d, %dms)\n",
			      cage_type, err, ms);
		return;
	}
		
	if (cmd.data0 == mxge_media_types[0].bitmask) {
		if (mxge_verbose)
			device_printf(sc->dev, "%s:%s\n", cage_type,
				      mxge_media_types[0].name);
		if (sc->current_media != mxge_media_types[0].flag) {
			mxge_media_init(sc);
			mxge_media_set(sc, mxge_media_types[0].flag);
		}
		return;
	}
	for (i = 1; i < mxge_media_type_entries; i++) {
		if (cmd.data0 & mxge_media_types[i].bitmask) {
			if (mxge_verbose)
				device_printf(sc->dev, "%s:%s\n",
					      cage_type,
					      mxge_media_types[i].name);

			if (sc->current_media != mxge_media_types[i].flag) {
				mxge_media_init(sc);
				mxge_media_set(sc, mxge_media_types[i].flag);
			}
			return;
		}
	}
	if (mxge_verbose)
		device_printf(sc->dev, "%s media 0x%x unknown\n",
			      cage_type, cmd.data0);

	return;
}