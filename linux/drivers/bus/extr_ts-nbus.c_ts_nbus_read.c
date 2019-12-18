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
typedef  int u8 ;
typedef  int u16 ;
struct ts_nbus {int /*<<< orphan*/  lock; int /*<<< orphan*/  rdy; int /*<<< orphan*/  csn; int /*<<< orphan*/  txrx; } ;

/* Variables and functions */
 int /*<<< orphan*/  TS_NBUS_DIRECTION_IN ; 
 int /*<<< orphan*/  TS_NBUS_DIRECTION_OUT ; 
 int /*<<< orphan*/  TS_NBUS_WRITE_ADR ; 
 int gpiod_get_value_cansleep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpiod_set_value_cansleep (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int ts_nbus_read_bus (struct ts_nbus*,int*) ; 
 int /*<<< orphan*/  ts_nbus_set_direction (struct ts_nbus*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ts_nbus_write_bus (struct ts_nbus*,int /*<<< orphan*/ ,int) ; 

int ts_nbus_read(struct ts_nbus *ts_nbus, u8 adr, u16 *val)
{
	int ret, i;
	u8 byte;

	/* bus access must be atomic */
	mutex_lock(&ts_nbus->lock);

	/* set the bus in read mode */
	gpiod_set_value_cansleep(ts_nbus->txrx, 0);

	/* write address */
	ts_nbus_write_bus(ts_nbus, TS_NBUS_WRITE_ADR, adr);

	/* set the data gpios direction as input before reading */
	ts_nbus_set_direction(ts_nbus, TS_NBUS_DIRECTION_IN);

	/* reading value MSB first */
	do {
		*val = 0;
		byte = 0;
		for (i = 1; i >= 0; i--) {
			/* read a byte from the bus, leave on error */
			ret = ts_nbus_read_bus(ts_nbus, &byte);
			if (ret < 0)
				goto err;

			/* append the byte read to the final value */
			*val |= byte << (i * 8);
		}
		gpiod_set_value_cansleep(ts_nbus->csn, 1);
		ret = gpiod_get_value_cansleep(ts_nbus->rdy);
	} while (ret);

err:
	/* restore the data gpios direction as output after reading */
	ts_nbus_set_direction(ts_nbus, TS_NBUS_DIRECTION_OUT);

	mutex_unlock(&ts_nbus->lock);

	return ret;
}