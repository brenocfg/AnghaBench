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

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*,unsigned int,unsigned int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  UCHCOM_REQ_WRITE_REG ; 
 int /*<<< orphan*/  uchcom_ctrl_write (struct uchcom_softc*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void
uchcom_write_reg(struct uchcom_softc *sc,
    uint8_t reg1, uint8_t val1, uint8_t reg2, uint8_t val2)
{
	DPRINTF("0x%02X<-0x%02X, 0x%02X<-0x%02X\n",
	    (unsigned)reg1, (unsigned)val1,
	    (unsigned)reg2, (unsigned)val2);
	uchcom_ctrl_write(
	    sc, UCHCOM_REQ_WRITE_REG,
	    reg1 | ((uint16_t)reg2 << 8), val1 | ((uint16_t)val2 << 8));
}