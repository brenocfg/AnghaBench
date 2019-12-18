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
typedef  int uint16_t ;
struct uchcom_softc {int dummy; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*,unsigned int,unsigned int,unsigned int,unsigned int) ; 
 int UCHCOM_INPUT_BUF_SIZE ; 
 int /*<<< orphan*/  UCHCOM_REQ_READ_REG ; 
 int /*<<< orphan*/  uchcom_ctrl_read (struct uchcom_softc*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static void
uchcom_read_reg(struct uchcom_softc *sc,
    uint8_t reg1, uint8_t *rval1, uint8_t reg2, uint8_t *rval2)
{
	uint8_t buf[UCHCOM_INPUT_BUF_SIZE];

	uchcom_ctrl_read(
	    sc, UCHCOM_REQ_READ_REG,
	    reg1 | ((uint16_t)reg2 << 8), 0, buf, sizeof(buf));

	DPRINTF("0x%02X->0x%02X, 0x%02X->0x%02X\n",
	    (unsigned)reg1, (unsigned)buf[0],
	    (unsigned)reg2, (unsigned)buf[1]);

	if (rval1)
		*rval1 = buf[0];
	if (rval2)
		*rval2 = buf[1];
}