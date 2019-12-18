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
struct hid_item {int unit; scalar_t__ logical_maximum; scalar_t__ logical_minimum; scalar_t__ physical_maximum; scalar_t__ physical_minimum; size_t unit_exponent; } ;
typedef  int int64_t ;
typedef  int int32_t ;

/* Variables and functions */
#define  HUM_CENTIMETER 131 
#define  HUM_DEGREE 130 
#define  HUM_INCH 129 
#define  HUM_RADIAN 128 
 int INT32_MAX ; 
 size_t nitems (int const**) ; 

int32_t
hid_item_resolution(struct hid_item *hi)
{
	/*
	 * hid unit scaling table according to HID Usage Table Review
	 * Request 39 Tbl 17 http://www.usb.org/developers/hidpage/HUTRR39b.pdf
	 */
	static const int64_t scale[0x10][2] = {
	    [0x00] = { 1, 1 },
	    [0x01] = { 1, 10 },
	    [0x02] = { 1, 100 },
	    [0x03] = { 1, 1000 },
	    [0x04] = { 1, 10000 },
	    [0x05] = { 1, 100000 },
	    [0x06] = { 1, 1000000 },
	    [0x07] = { 1, 10000000 },
	    [0x08] = { 100000000, 1 },
	    [0x09] = { 10000000, 1 },
	    [0x0A] = { 1000000, 1 },
	    [0x0B] = { 100000, 1 },
	    [0x0C] = { 10000, 1 },
	    [0x0D] = { 1000, 1 },
	    [0x0E] = { 100, 1 },
	    [0x0F] = { 10, 1 },
	};
	int64_t logical_size;
	int64_t physical_size;
	int64_t multiplier;
	int64_t divisor;
	int64_t resolution;

	switch (hi->unit) {
	case HUM_CENTIMETER:
		multiplier = 1;
		divisor = 10;
		break;
	case HUM_INCH:
		multiplier = 10;
		divisor = 254;
		break;
	case HUM_RADIAN:
		multiplier = 1;
		divisor = 1;
		break;
	case HUM_DEGREE:
		multiplier = 573;
		divisor = 10;
		break;
	default:
		return (0);
	}

	if ((hi->logical_maximum <= hi->logical_minimum) ||
	    (hi->physical_maximum <= hi->physical_minimum) ||
	    (hi->unit_exponent < 0) || (hi->unit_exponent >= nitems(scale)))
		return (0);

	logical_size = (int64_t)hi->logical_maximum -
	    (int64_t)hi->logical_minimum;
	physical_size = (int64_t)hi->physical_maximum -
	    (int64_t)hi->physical_minimum;
	/* Round to ceiling */
	resolution = logical_size * multiplier * scale[hi->unit_exponent][0] /
	    (physical_size * divisor * scale[hi->unit_exponent][1]);

	if (resolution > INT32_MAX)
		return (0);

	return (resolution);
}