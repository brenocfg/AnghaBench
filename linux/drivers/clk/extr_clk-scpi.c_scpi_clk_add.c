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
typedef  int /*<<< orphan*/  u32 ;
struct scpi_clk_data {int clk_num; struct scpi_clk** clk; } ;
struct scpi_clk {int /*<<< orphan*/  id; } ;
struct of_device_id {int dummy; } ;
typedef  char const device_node ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,char const*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,char const*) ; 
 struct scpi_clk** devm_kcalloc (struct device*,int,int,int /*<<< orphan*/ ) ; 
 struct scpi_clk_data* devm_kmalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 struct scpi_clk* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int of_clk_add_hw_provider (char const*,int /*<<< orphan*/ ,struct scpi_clk_data*) ; 
 int of_property_count_strings (char const*,char*) ; 
 scalar_t__ of_property_read_string_index (char const*,char*,int,char const**) ; 
 scalar_t__ of_property_read_u32_index (char const*,char*,int,int /*<<< orphan*/ *) ; 
 int scpi_clk_ops_init (struct device*,struct of_device_id const*,struct scpi_clk*,char const*) ; 
 int /*<<< orphan*/  scpi_of_clk_src_get ; 

__attribute__((used)) static int scpi_clk_add(struct device *dev, struct device_node *np,
			const struct of_device_id *match)
{
	int idx, count, err;
	struct scpi_clk_data *clk_data;

	count = of_property_count_strings(np, "clock-output-names");
	if (count < 0) {
		dev_err(dev, "%pOFn: invalid clock output count\n", np);
		return -EINVAL;
	}

	clk_data = devm_kmalloc(dev, sizeof(*clk_data), GFP_KERNEL);
	if (!clk_data)
		return -ENOMEM;

	clk_data->clk_num = count;
	clk_data->clk = devm_kcalloc(dev, count, sizeof(*clk_data->clk),
				     GFP_KERNEL);
	if (!clk_data->clk)
		return -ENOMEM;

	for (idx = 0; idx < count; idx++) {
		struct scpi_clk *sclk;
		const char *name;
		u32 val;

		sclk = devm_kzalloc(dev, sizeof(*sclk), GFP_KERNEL);
		if (!sclk)
			return -ENOMEM;

		if (of_property_read_string_index(np, "clock-output-names",
						  idx, &name)) {
			dev_err(dev, "invalid clock name @ %pOFn\n", np);
			return -EINVAL;
		}

		if (of_property_read_u32_index(np, "clock-indices",
					       idx, &val)) {
			dev_err(dev, "invalid clock index @ %pOFn\n", np);
			return -EINVAL;
		}

		sclk->id = val;

		err = scpi_clk_ops_init(dev, match, sclk, name);
		if (err) {
			dev_err(dev, "failed to register clock '%s'\n", name);
			return err;
		}

		dev_dbg(dev, "Registered clock '%s'\n", name);
		clk_data->clk[idx] = sclk;
	}

	return of_clk_add_hw_provider(np, scpi_of_clk_src_get, clk_data);
}