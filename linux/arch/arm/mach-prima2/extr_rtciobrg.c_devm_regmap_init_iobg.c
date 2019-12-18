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
struct regmap_config {int dummy; } ;
struct regmap_bus {int dummy; } ;
struct regmap {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct regmap* devm_regmap_init (struct device*,struct regmap_bus const*,struct device*,struct regmap_config const*) ; 
 struct regmap_bus regmap_iobg ; 

struct regmap *devm_regmap_init_iobg(struct device *dev,
				    const struct regmap_config *config)
{
	const struct regmap_bus *bus = &regmap_iobg;

	return devm_regmap_init(dev, bus, dev, config);
}