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
 int /*<<< orphan*/  I2CSTAT ; 
 int READ1 (struct i2c_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
is_ack(struct i2c_softc *sc)
{
	int stat;

	stat = READ1(sc, I2CSTAT);
	if (!(stat & 1)) {
		/* ACK received */
		return (1);
	}

	return (0);
}