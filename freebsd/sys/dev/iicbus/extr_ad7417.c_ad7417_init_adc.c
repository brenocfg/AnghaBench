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
typedef  int /*<<< orphan*/  uint32_t ;
struct ad7417_softc {int init_done; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  AD7417_CONFIG ; 
 int /*<<< orphan*/  AD7417_CONFIG2 ; 
 int ad7417_read_1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int ad7417_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int adc741x_config ; 
 struct ad7417_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ad7417_init_adc(device_t dev, uint32_t addr)
{
	uint8_t buf;
	int err;
	struct ad7417_softc *sc;

	sc = device_get_softc(dev);

	adc741x_config = 0;
	/* Clear Config2 */
	buf = 0;

	err = ad7417_write(dev, addr, AD7417_CONFIG2, &buf, 1);

	 /* Read & cache Config1 */
	buf = 0;
	err = ad7417_write(dev, addr, AD7417_CONFIG, &buf, 1);
	err = ad7417_read_1(dev, addr, AD7417_CONFIG, &buf);
	adc741x_config = (uint8_t)buf;

	/* Disable shutdown mode */
	adc741x_config &= 0xfe;
	buf = adc741x_config;
	err = ad7417_write(dev, addr, AD7417_CONFIG, &buf, 1);
	if (err < 0)
		return (-1);

	sc->init_done = 1;

	return (0);

}