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
typedef  scalar_t__ uint8_t ;
typedef  int uint32_t ;
typedef  int uint16_t ;
struct muge_softc {int /*<<< orphan*/  sc_mtx; } ;

/* Variables and functions */
 int /*<<< orphan*/  MUGE_LOCK (struct muge_softc*) ; 
 int /*<<< orphan*/  MUGE_UNLOCK (struct muge_softc*) ; 
 int /*<<< orphan*/  OTP_ADDR1 ; 
 int OTP_ADDR1_15_11 ; 
 int /*<<< orphan*/  OTP_ADDR2 ; 
 int OTP_ADDR2_10_3 ; 
 int /*<<< orphan*/  OTP_CMD_GO ; 
 int OTP_CMD_GO_GO_ ; 
 int /*<<< orphan*/  OTP_FUNC_CMD ; 
 int OTP_FUNC_CMD_READ_ ; 
 int /*<<< orphan*/  OTP_PWR_DN ; 
 int OTP_PWR_DN_PWRDN_N ; 
 int /*<<< orphan*/  OTP_RD_DATA ; 
 int /*<<< orphan*/  OTP_STATUS ; 
 int OTP_STATUS_BUSY_ ; 
 int lan78xx_read_reg (struct muge_softc*,int /*<<< orphan*/ ,int*) ; 
 int lan78xx_wait_for_bits (struct muge_softc*,int /*<<< orphan*/ ,int) ; 
 int lan78xx_write_reg (struct muge_softc*,int /*<<< orphan*/ ,int) ; 
 int mtx_owned (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  muge_warn_printf (struct muge_softc*,char*) ; 

__attribute__((used)) static int
lan78xx_otp_read_raw(struct muge_softc *sc, uint16_t off, uint8_t *buf,
    uint16_t buflen)
{
	int locked, err;
	uint32_t val;
	uint16_t i;
	locked = mtx_owned(&sc->sc_mtx);
	if (!locked)
		MUGE_LOCK(sc);

	err = lan78xx_read_reg(sc, OTP_PWR_DN, &val);

	/* Checking if bit is set. */
	if (val & OTP_PWR_DN_PWRDN_N) {
		/* Clear it, then wait for it to be cleared. */
		lan78xx_write_reg(sc, OTP_PWR_DN, 0);
		err = lan78xx_wait_for_bits(sc, OTP_PWR_DN, OTP_PWR_DN_PWRDN_N);
		if (err != 0) {
			muge_warn_printf(sc, "OTP off? failed to read data\n");
			goto done;
		}
	}
	/* Start reading the bytes, one at a time. */
	for (i = 0; i < buflen; i++) {
		err = lan78xx_write_reg(sc, OTP_ADDR1,
		    ((off + i) >> 8) & OTP_ADDR1_15_11);
		err = lan78xx_write_reg(sc, OTP_ADDR2,
		    ((off + i) & OTP_ADDR2_10_3));
		err = lan78xx_write_reg(sc, OTP_FUNC_CMD, OTP_FUNC_CMD_READ_);
		err = lan78xx_write_reg(sc, OTP_CMD_GO, OTP_CMD_GO_GO_);

		err = lan78xx_wait_for_bits(sc, OTP_STATUS, OTP_STATUS_BUSY_);
		if (err != 0) {
			muge_warn_printf(sc, "OTP busy failed to read data\n");
			goto done;
		}

		if ((err = lan78xx_read_reg(sc, OTP_RD_DATA, &val)) != 0)
			goto done;

		buf[i] = (uint8_t)(val & 0xff);
	}

done:
	if (!locked)
		MUGE_UNLOCK(sc);
	return (err);
}