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
struct regmap_config {int val_format_endian; } ;
struct regmap_bus {int val_format_endian_default; } ;
struct device_node {int dummy; } ;
struct device {struct device_node* of_node; } ;
typedef  enum regmap_endian { ____Placeholder_regmap_endian } regmap_endian ;

/* Variables and functions */
 int REGMAP_ENDIAN_BIG ; 
 int REGMAP_ENDIAN_DEFAULT ; 
 int REGMAP_ENDIAN_LITTLE ; 
 int REGMAP_ENDIAN_NATIVE ; 
 scalar_t__ of_property_read_bool (struct device_node*,char*) ; 

enum regmap_endian regmap_get_val_endian(struct device *dev,
					 const struct regmap_bus *bus,
					 const struct regmap_config *config)
{
	struct device_node *np;
	enum regmap_endian endian;

	/* Retrieve the endianness specification from the regmap config */
	endian = config->val_format_endian;

	/* If the regmap config specified a non-default value, use that */
	if (endian != REGMAP_ENDIAN_DEFAULT)
		return endian;

	/* If the dev and dev->of_node exist try to get endianness from DT */
	if (dev && dev->of_node) {
		np = dev->of_node;

		/* Parse the device's DT node for an endianness specification */
		if (of_property_read_bool(np, "big-endian"))
			endian = REGMAP_ENDIAN_BIG;
		else if (of_property_read_bool(np, "little-endian"))
			endian = REGMAP_ENDIAN_LITTLE;
		else if (of_property_read_bool(np, "native-endian"))
			endian = REGMAP_ENDIAN_NATIVE;

		/* If the endianness was specified in DT, use that */
		if (endian != REGMAP_ENDIAN_DEFAULT)
			return endian;
	}

	/* Retrieve the endianness specification from the bus config */
	if (bus && bus->val_format_endian_default)
		endian = bus->val_format_endian_default;

	/* If the bus specified a non-default value, use that */
	if (endian != REGMAP_ENDIAN_DEFAULT)
		return endian;

	/* Use this if no other value was found */
	return REGMAP_ENDIAN_BIG;
}