#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;
typedef  struct TYPE_14__   TYPE_12__ ;

/* Type definitions */
struct i2c_device_id {int dummy; } ;
struct TYPE_17__ {TYPE_2__* of_node; } ;
struct i2c_client {TYPE_5__ dev; } ;
struct clk_si5341_output_config {int out_format_drv_bits; int out_cm_ampl_bits; scalar_t__ always_on; scalar_t__ synth_master; } ;
struct TYPE_18__ {int /*<<< orphan*/  clk; struct clk_init_data* init; } ;
struct clk_si5341 {char const* pxtal_name; unsigned int num_synth; unsigned int num_outputs; int /*<<< orphan*/  regmap; TYPE_12__* clk; TYPE_1__* synth; TYPE_9__ hw; int /*<<< orphan*/  pxtal; struct i2c_client* i2c_client; } ;
struct clk_init_data {char* name; char const** parent_names; int num_parents; int /*<<< orphan*/  flags; int /*<<< orphan*/ * ops; } ;
struct TYPE_16__ {char* name; } ;
struct TYPE_15__ {unsigned int index; TYPE_9__ hw; struct clk_si5341* data; } ;
struct TYPE_14__ {unsigned int index; TYPE_9__ hw; struct clk_si5341* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CLK_SET_RATE_PARENT ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int SI5341_MAX_NUM_OUTPUTS ; 
 int SI5341_NUM_SYNTH ; 
 int /*<<< orphan*/  SI5341_OUT_CM (TYPE_12__*) ; 
 int /*<<< orphan*/  SI5341_OUT_FORMAT (TYPE_12__*) ; 
 char const* __clk_get_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_prepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (TYPE_5__*,char*,...) ; 
 int /*<<< orphan*/  devm_clk_get (TYPE_5__*,char*) ; 
 int devm_clk_hw_register (TYPE_5__*,TYPE_9__*) ; 
 char* devm_kasprintf (TYPE_5__*,int /*<<< orphan*/ ,char*,char*,unsigned int) ; 
 int /*<<< orphan*/  devm_kfree (TYPE_5__*,void*) ; 
 struct clk_si5341* devm_kzalloc (TYPE_5__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_regmap_init_i2c (struct i2c_client*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct clk_si5341*) ; 
 char const* kasprintf (int /*<<< orphan*/ ,char*,char*,unsigned int) ; 
 int /*<<< orphan*/  kfree (char const*) ; 
 int of_clk_add_hw_provider (TYPE_2__*,int /*<<< orphan*/ ,struct clk_si5341*) ; 
 int /*<<< orphan*/  of_clk_si5341_get ; 
 scalar_t__ of_property_read_bool (TYPE_2__*,char*) ; 
 scalar_t__ of_property_read_string (TYPE_2__*,char*,char**) ; 
 int /*<<< orphan*/  regcache_cache_only (int /*<<< orphan*/ ,int) ; 
 int regcache_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  si5341_clk_ops ; 
 int si5341_dt_parse_dt (struct i2c_client*,struct clk_si5341_output_config*) ; 
 int si5341_finalize_defaults (struct clk_si5341*) ; 
 int si5341_initialize_pll (struct clk_si5341*) ; 
 int si5341_is_programmed_already (struct clk_si5341*) ; 
 int /*<<< orphan*/  si5341_output_clk_ops ; 
 int si5341_probe_chip_id (struct clk_si5341*) ; 
 int si5341_read_settings (struct clk_si5341*) ; 
 int /*<<< orphan*/  si5341_reg_defaults ; 
 int /*<<< orphan*/  si5341_regmap_config ; 
 int si5341_send_preamble (struct clk_si5341*) ; 
 int /*<<< orphan*/  si5341_synth_clk_ops ; 
 int si5341_write_multiple (struct clk_si5341*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int si5341_probe(struct i2c_client *client,
		const struct i2c_device_id *id)
{
	struct clk_si5341 *data;
	struct clk_init_data init;
	const char *root_clock_name;
	const char *synth_clock_names[SI5341_NUM_SYNTH];
	int err;
	unsigned int i;
	struct clk_si5341_output_config config[SI5341_MAX_NUM_OUTPUTS];
	bool initialization_required;

	data = devm_kzalloc(&client->dev, sizeof(*data), GFP_KERNEL);
	if (!data)
		return -ENOMEM;

	data->i2c_client = client;

	data->pxtal = devm_clk_get(&client->dev, "xtal");
	if (IS_ERR(data->pxtal)) {
		if (PTR_ERR(data->pxtal) == -EPROBE_DEFER)
			return -EPROBE_DEFER;

		dev_err(&client->dev, "Missing xtal clock input\n");
	}

	err = si5341_dt_parse_dt(client, config);
	if (err)
		return err;

	if (of_property_read_string(client->dev.of_node, "clock-output-names",
			&init.name))
		init.name = client->dev.of_node->name;
	root_clock_name = init.name;

	data->regmap = devm_regmap_init_i2c(client, &si5341_regmap_config);
	if (IS_ERR(data->regmap))
		return PTR_ERR(data->regmap);

	i2c_set_clientdata(client, data);

	err = si5341_probe_chip_id(data);
	if (err < 0)
		return err;

	/* "Activate" the xtal (usually a fixed clock) */
	clk_prepare_enable(data->pxtal);

	if (of_property_read_bool(client->dev.of_node, "silabs,reprogram")) {
		initialization_required = true;
	} else {
		err = si5341_is_programmed_already(data);
		if (err < 0)
			return err;

		initialization_required = !err;
	}

	if (initialization_required) {
		/* Populate the regmap cache in preparation for "cache only" */
		err = si5341_read_settings(data);
		if (err < 0)
			return err;

		err = si5341_send_preamble(data);
		if (err < 0)
			return err;

		/*
		 * We intend to send all 'final' register values in a single
		 * transaction. So cache all register writes until we're done
		 * configuring.
		 */
		regcache_cache_only(data->regmap, true);

		/* Write the configuration pairs from the firmware blob */
		err = si5341_write_multiple(data, si5341_reg_defaults,
					ARRAY_SIZE(si5341_reg_defaults));
		if (err < 0)
			return err;

		/* PLL configuration is required */
		err = si5341_initialize_pll(data);
		if (err < 0)
			return err;
	}

	/* Register the PLL */
	data->pxtal_name = __clk_get_name(data->pxtal);
	init.parent_names = &data->pxtal_name;
	init.num_parents = 1; /* For now, only XTAL input supported */
	init.ops = &si5341_clk_ops;
	init.flags = 0;
	data->hw.init = &init;

	err = devm_clk_hw_register(&client->dev, &data->hw);
	if (err) {
		dev_err(&client->dev, "clock registration failed\n");
		return err;
	}

	init.num_parents = 1;
	init.parent_names = &root_clock_name;
	init.ops = &si5341_synth_clk_ops;
	for (i = 0; i < data->num_synth; ++i) {
		synth_clock_names[i] = devm_kasprintf(&client->dev, GFP_KERNEL,
				"%s.N%u", client->dev.of_node->name, i);
		init.name = synth_clock_names[i];
		data->synth[i].index = i;
		data->synth[i].data = data;
		data->synth[i].hw.init = &init;
		err = devm_clk_hw_register(&client->dev, &data->synth[i].hw);
		if (err) {
			dev_err(&client->dev,
				"synth N%u registration failed\n", i);
		}
	}

	init.num_parents = data->num_synth;
	init.parent_names = synth_clock_names;
	init.ops = &si5341_output_clk_ops;
	for (i = 0; i < data->num_outputs; ++i) {
		init.name = kasprintf(GFP_KERNEL, "%s.%d",
			client->dev.of_node->name, i);
		init.flags = config[i].synth_master ? CLK_SET_RATE_PARENT : 0;
		data->clk[i].index = i;
		data->clk[i].data = data;
		data->clk[i].hw.init = &init;
		if (config[i].out_format_drv_bits & 0x07) {
			regmap_write(data->regmap,
				SI5341_OUT_FORMAT(&data->clk[i]),
				config[i].out_format_drv_bits);
			regmap_write(data->regmap,
				SI5341_OUT_CM(&data->clk[i]),
				config[i].out_cm_ampl_bits);
		}
		err = devm_clk_hw_register(&client->dev, &data->clk[i].hw);
		kfree(init.name); /* clock framework made a copy of the name */
		if (err) {
			dev_err(&client->dev,
				"output %u registration failed\n", i);
			return err;
		}
		if (config[i].always_on)
			clk_prepare(data->clk[i].hw.clk);
	}

	err = of_clk_add_hw_provider(client->dev.of_node, of_clk_si5341_get,
			data);
	if (err) {
		dev_err(&client->dev, "unable to add clk provider\n");
		return err;
	}

	if (initialization_required) {
		/* Synchronize */
		regcache_cache_only(data->regmap, false);
		err = regcache_sync(data->regmap);
		if (err < 0)
			return err;

		err = si5341_finalize_defaults(data);
		if (err < 0)
			return err;
	}

	/* Free the names, clk framework makes copies */
	for (i = 0; i < data->num_synth; ++i)
		 devm_kfree(&client->dev, (void *)synth_clock_names[i]);

	return 0;
}