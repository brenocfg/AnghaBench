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
typedef  int /*<<< orphan*/  uint8_t ;
struct uchcom_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  UCHCOM_REG_STAT1 ; 
 int /*<<< orphan*/  uchcom_write_reg (struct uchcom_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
uchcom_set_dtr_rts_10(struct uchcom_softc *sc, uint8_t val)
{
	uchcom_write_reg(sc, UCHCOM_REG_STAT1, val, UCHCOM_REG_STAT1, val);
}