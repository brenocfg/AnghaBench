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
struct i2c_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  I2C_IBSR ; 
 int IBSR_IBIF ; 
 int IBSR_TCF ; 
 int IIC_ETIMEOUT ; 
 int IIC_NOERR ; 
 int READ1 (struct i2c_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE1 (struct i2c_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
wait_for_icf(struct i2c_softc *sc)
{
	int retry;

	retry = 1000;
	while (retry --) {
		if (READ1(sc, I2C_IBSR) & IBSR_TCF) {
			if (READ1(sc, I2C_IBSR) & IBSR_IBIF) {
				WRITE1(sc, I2C_IBSR, IBSR_IBIF);
				return (IIC_NOERR);
			}
		}
		DELAY(10);
	}

	return (IIC_ETIMEOUT);
}