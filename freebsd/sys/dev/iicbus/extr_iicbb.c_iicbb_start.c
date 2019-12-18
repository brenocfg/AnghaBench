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
typedef  int /*<<< orphan*/  u_char ;
struct iicbb_softc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  I2C_DEBUG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I2C_GETSCL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I2C_SET (struct iicbb_softc*,int /*<<< orphan*/ ,int,int) ; 
 int IIC_ETIMEOUT ; 
 struct iicbb_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int iicbb_ack (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  iicbb_sendbyte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  iicbb_stop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static int
iicbb_start(device_t dev, u_char slave, int timeout)
{
	struct iicbb_softc *sc = device_get_softc(dev);
	int error;

	I2C_DEBUG(printf("<"));

	I2C_SET(sc,dev,1,1);

	/* SCL must be high now. */
	if (!I2C_GETSCL(dev))
		return (IIC_ETIMEOUT);

	I2C_SET(sc,dev,1,0);
	I2C_SET(sc,dev,0,0);

	/* send address */
	iicbb_sendbyte(dev, slave, timeout);

	/* check for ack */
	error = iicbb_ack(dev, timeout);
	if (error == 0)
		return (0);

	iicbb_stop(dev);
	return (error);
}