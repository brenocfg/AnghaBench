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
struct iicbb_softc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  I2C_DEBUG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I2C_GETSCL (int /*<<< orphan*/ ) ; 
 int I2C_GETSDA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I2C_SET (struct iicbb_softc*,int /*<<< orphan*/ ,int,int) ; 
 int IIC_ENOACK ; 
 int IIC_ETIMEOUT ; 
 struct iicbb_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char) ; 

__attribute__((used)) static int
iicbb_ack(device_t dev, int timeout)
{
	struct iicbb_softc *sc = device_get_softc(dev);
	int noack;
	int k = 0;

	I2C_SET(sc,dev,0,1);
	I2C_SET(sc,dev,1,1);

	/* SCL must be high now. */
	if (!I2C_GETSCL(dev))
		return (IIC_ETIMEOUT);

	do {
		noack = I2C_GETSDA(dev);
		if (!noack)
			break;
		DELAY(1);
		k++;
	} while (k < timeout);

	I2C_SET(sc,dev,0,1);
	I2C_DEBUG(printf("%c ",noack?'-':'+'));

	return (noack ? IIC_ENOACK : 0);
}