#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct sdma_engine {TYPE_1__* dev; } ;
struct regmap {int dummy; } ;
struct property {int length; } ;
typedef  struct regmap device_node ;
struct TYPE_3__ {struct regmap* of_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 int EINVAL ; 
 int EVENT_REMAP_CELLS ; 
 scalar_t__ IS_ERR (struct regmap*) ; 
 int PTR_ERR (struct regmap*) ; 
 int /*<<< orphan*/  dev_dbg (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,...) ; 
 struct property* of_find_property (struct regmap*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_node_put (struct regmap*) ; 
 struct regmap* of_parse_phandle (struct regmap*,char*,int /*<<< orphan*/ ) ; 
 int of_property_read_u32_index (struct regmap*,char*,int,int*) ; 
 int /*<<< orphan*/  regmap_update_bits (struct regmap*,int,int /*<<< orphan*/ ,int) ; 
 struct regmap* syscon_node_to_regmap (struct regmap*) ; 

__attribute__((used)) static int sdma_event_remap(struct sdma_engine *sdma)
{
	struct device_node *np = sdma->dev->of_node;
	struct device_node *gpr_np = of_parse_phandle(np, "gpr", 0);
	struct property *event_remap;
	struct regmap *gpr;
	char propname[] = "fsl,sdma-event-remap";
	u32 reg, val, shift, num_map, i;
	int ret = 0;

	if (IS_ERR(np) || IS_ERR(gpr_np))
		goto out;

	event_remap = of_find_property(np, propname, NULL);
	num_map = event_remap ? (event_remap->length / sizeof(u32)) : 0;
	if (!num_map) {
		dev_dbg(sdma->dev, "no event needs to be remapped\n");
		goto out;
	} else if (num_map % EVENT_REMAP_CELLS) {
		dev_err(sdma->dev, "the property %s must modulo %d\n",
				propname, EVENT_REMAP_CELLS);
		ret = -EINVAL;
		goto out;
	}

	gpr = syscon_node_to_regmap(gpr_np);
	if (IS_ERR(gpr)) {
		dev_err(sdma->dev, "failed to get gpr regmap\n");
		ret = PTR_ERR(gpr);
		goto out;
	}

	for (i = 0; i < num_map; i += EVENT_REMAP_CELLS) {
		ret = of_property_read_u32_index(np, propname, i, &reg);
		if (ret) {
			dev_err(sdma->dev, "failed to read property %s index %d\n",
					propname, i);
			goto out;
		}

		ret = of_property_read_u32_index(np, propname, i + 1, &shift);
		if (ret) {
			dev_err(sdma->dev, "failed to read property %s index %d\n",
					propname, i + 1);
			goto out;
		}

		ret = of_property_read_u32_index(np, propname, i + 2, &val);
		if (ret) {
			dev_err(sdma->dev, "failed to read property %s index %d\n",
					propname, i + 2);
			goto out;
		}

		regmap_update_bits(gpr, reg, BIT(shift), val << shift);
	}

out:
	if (!IS_ERR(gpr_np))
		of_node_put(gpr_np);

	return ret;
}