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
typedef  int uint32_t ;
struct write_data {int val; int /*<<< orphan*/  reg; } ;
struct read_data {scalar_t__ val; int /*<<< orphan*/  reg; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  AD7417_ADC ; 
 int /*<<< orphan*/  AD7417_CONFIG ; 
 int AD7417_CONFMASK ; 
 int ad7417_read_1 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int*) ; 
 int ad7417_write_read (int /*<<< orphan*/ ,int,struct write_data,struct read_data*) ; 

__attribute__((used)) static int
ad7417_get_adc(device_t dev, uint32_t addr, unsigned int *value,
	       uint8_t chan)
{
	uint8_t tmp;
	int err;
	struct write_data config;
	struct read_data data;

	tmp = chan << 5;
	config.reg = AD7417_CONFIG;
	data.reg = AD7417_ADC;
	data.val = 0;

	err = ad7417_read_1(dev, addr, AD7417_CONFIG, &config.val);

	config.val = (config.val & ~AD7417_CONFMASK) | (tmp & AD7417_CONFMASK);

	err = ad7417_write_read(dev, addr, config, &data);
	if (err < 0)
		return (-1);

	*value = ((uint32_t)data.val) >> 6;

	return (0);
}