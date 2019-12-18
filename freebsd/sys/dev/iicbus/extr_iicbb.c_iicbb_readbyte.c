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
typedef  unsigned char u_char ;
struct iicbb_softc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  I2C_DEBUG (int /*<<< orphan*/ ) ; 
 scalar_t__ I2C_GETSDA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I2C_SET (struct iicbb_softc*,int /*<<< orphan*/ ,int,int) ; 
 struct iicbb_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iicbb_one (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  iicbb_zero (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,int,char) ; 

__attribute__((used)) static u_char
iicbb_readbyte(device_t dev, int last, int timeout)
{
	struct iicbb_softc *sc = device_get_softc(dev);
	int i;
	unsigned char data=0;

	I2C_SET(sc,dev,0,1);
	for (i=7; i>=0; i--) 
	{
		I2C_SET(sc,dev,1,1);
		if (I2C_GETSDA(dev))
			data |= (1<<i);
		I2C_SET(sc,dev,0,1);
	}
	if (last) {
		iicbb_one(dev, timeout);
	} else {
		iicbb_zero(dev, timeout);
	}
	I2C_DEBUG(printf("r%02x%c ",(int)data,last?'-':'+'));
	return (data);
}