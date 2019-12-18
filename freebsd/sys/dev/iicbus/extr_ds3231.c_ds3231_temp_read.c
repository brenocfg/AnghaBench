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
struct ds3231_softc {int /*<<< orphan*/  sc_dev; } ;
typedef  int int16_t ;
typedef  int /*<<< orphan*/  buf8 ;

/* Variables and functions */
 int DS3231_0250C ; 
 int DS3231_0500C ; 
 int DS3231_NEG_BIT ; 
 int /*<<< orphan*/  DS3231_TEMP ; 
 int DS3231_TEMP_MASK ; 
 int /*<<< orphan*/  IIC_INTRWAIT ; 
 scalar_t__ TZ_ZEROC ; 
 int iicdev_readfrom (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ds3231_temp_read(struct ds3231_softc *sc, int *temp)
{
	int error, neg, t;
	uint8_t buf8[2];
	uint16_t buf;

	error = iicdev_readfrom(sc->sc_dev, DS3231_TEMP, buf8, sizeof(buf8),
	    IIC_INTRWAIT);
	if (error != 0)
		return (error);
	buf = (buf8[0] << 8) | (buf8[1] & 0xff);
	neg = 0;
	if (buf & DS3231_NEG_BIT) {
		buf = ~(buf & DS3231_TEMP_MASK) + 1;
		neg = 1;
	}
	*temp = ((int16_t)buf >> 8) * 10;
	t = 0;
	if (buf & DS3231_0250C)
		t += 250;
	if (buf & DS3231_0500C)
		t += 500;
	t /= 100;
	*temp += t;
	if (neg)
		*temp = -(*temp);
	*temp += TZ_ZEROC;

	return (0);
}