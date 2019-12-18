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
typedef  int uint8_t ;
struct iic_msg {int member_0; int member_2; int* member_3; int /*<<< orphan*/  member_1; } ;
struct ec_softc {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EC_CMD_VERSION0 ; 
 int /*<<< orphan*/  IIC_M_RD ; 
 int /*<<< orphan*/  IIC_M_WR ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 struct ec_softc* ec_sc ; 
 int /*<<< orphan*/  fill_checksum (int*,int) ; 
 int /*<<< orphan*/  free (int*,int /*<<< orphan*/ ) ; 
 int iicbus_transfer (int /*<<< orphan*/ ,struct iic_msg*,int) ; 
 int* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
ec_command(uint8_t cmd, uint8_t *dout, uint8_t dout_len,
    uint8_t *dinp, uint8_t dinp_len)
{
	struct ec_softc *sc;
	uint8_t *msg_dout;
	uint8_t *msg_dinp;
	int ret;
	int i;

	msg_dout = malloc(dout_len + 4, M_DEVBUF, M_NOWAIT);
	msg_dinp = malloc(dinp_len + 3, M_DEVBUF, M_NOWAIT);

	if (ec_sc == NULL)
		return (-1);

	sc = ec_sc;

	msg_dout[0] = EC_CMD_VERSION0;
	msg_dout[1] = cmd;
	msg_dout[2] = dout_len;

	for (i = 0; i < dout_len; i++) {
		msg_dout[i + 3] = dout[i];
	}

	fill_checksum(msg_dout, dout_len + 3);

	struct iic_msg msgs[] = {
		{ 0x1e, IIC_M_WR, dout_len + 4, msg_dout, },
		{ 0x1e, IIC_M_RD, dinp_len + 3, msg_dinp, },
	};

	ret = iicbus_transfer(sc->dev, msgs, 2);
	if (ret != 0) {
		device_printf(sc->dev, "i2c transfer returned %d\n", ret);
		free(msg_dout, M_DEVBUF);
		free(msg_dinp, M_DEVBUF);
		return (-1);
	}

	for (i = 0; i < dinp_len; i++) {
		dinp[i] = msg_dinp[i + 2];
	}

	free(msg_dout, M_DEVBUF);
	free(msg_dinp, M_DEVBUF);
	return (0);
}