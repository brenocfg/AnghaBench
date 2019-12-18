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
typedef  size_t uint16_t ;
struct timespec {int dummy; } ;
struct jzsmb_softc {int dummy; } ;
struct iic_msg {int len; size_t* buf; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int EIO ; 
 int JZSMB_TIMEOUT ; 
 int /*<<< orphan*/  SMBCON ; 
 size_t SMBCON_STPHLD ; 
 int /*<<< orphan*/  SMBDC ; 
 int /*<<< orphan*/  SMBST ; 
 size_t SMBST_TFNF ; 
 int /*<<< orphan*/  SMB_ASSERT_LOCKED (struct jzsmb_softc*) ; 
 size_t SMB_READ (struct jzsmb_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SMB_WRITE (struct jzsmb_softc*,int /*<<< orphan*/ ,size_t) ; 
 struct jzsmb_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,size_t) ; 
 int /*<<< orphan*/  getnanouptime (struct timespec*) ; 
 int hz ; 
 int /*<<< orphan*/  timespecsub (struct timespec*,struct timespec*,struct timespec*) ; 
 int tstohz (struct timespec*) ; 

__attribute__((used)) static int
jzsmb_transfer_write(device_t dev, struct iic_msg *msg, int stop_hold)
{
	struct jzsmb_softc *sc;
	struct timespec start, diff;
	uint16_t con, resid;
	int timeo;

	sc = device_get_softc(dev);
	timeo = JZSMB_TIMEOUT * msg->len;

	SMB_ASSERT_LOCKED(sc);

	con = SMB_READ(sc, SMBCON);
	con |= SMBCON_STPHLD;
	SMB_WRITE(sc, SMBCON, con);

	getnanouptime(&start);
	for (resid = msg->len; resid > 0; resid--) {
		for (;;) {
			getnanouptime(&diff);
			timespecsub(&diff, &start, &diff);
			if ((SMB_READ(sc, SMBST) & SMBST_TFNF) != 0) {
				SMB_WRITE(sc, SMBDC,
				    msg->buf[msg->len - resid]);
				break;
			} else
				DELAY((1000 * hz) / JZSMB_TIMEOUT);

			if (tstohz(&diff) >= timeo) {
				device_printf(dev,
				    "write timeout (status=0x%02x)\n",
				    SMB_READ(sc, SMBST));
				return (EIO);
			}
		}
	}

	if (!stop_hold) {
		con = SMB_READ(sc, SMBCON);
		con &= ~SMBCON_STPHLD;
		SMB_WRITE(sc, SMBCON, con);
	}

	return (0);
}