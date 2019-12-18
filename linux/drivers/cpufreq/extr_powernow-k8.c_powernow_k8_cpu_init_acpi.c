#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
struct TYPE_5__ {scalar_t__ space_id; } ;
struct TYPE_4__ {scalar_t__ space_id; } ;
struct TYPE_6__ {int state_count; int /*<<< orphan*/  shared_cpu_map; TYPE_2__ status_register; TYPE_1__ control_register; } ;
struct powernow_k8_data {scalar_t__ cpu; int numps; TYPE_3__ acpi_data; struct cpufreq_frequency_table* powernow_table; } ;
struct cpufreq_frequency_table {int /*<<< orphan*/  frequency; } ;

/* Variables and functions */
 scalar_t__ ACPI_ADR_SPACE_FIXED_HARDWARE ; 
 int /*<<< orphan*/  CPUFREQ_TABLE_END ; 
 int EIO ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  acpi_processor_notify_smm (int /*<<< orphan*/ ) ; 
 scalar_t__ acpi_processor_register_performance (TYPE_3__*,scalar_t__) ; 
 int /*<<< orphan*/  acpi_processor_unregister_performance (scalar_t__) ; 
 scalar_t__ cpumask_first (int /*<<< orphan*/ ) ; 
 int fill_powernow_table_fidvid (struct powernow_k8_data*,struct cpufreq_frequency_table*) ; 
 int /*<<< orphan*/  kfree (struct cpufreq_frequency_table*) ; 
 struct cpufreq_frequency_table* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  powernow_k8_acpi_pst_values (struct powernow_k8_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  print_basics (struct powernow_k8_data*) ; 
 int /*<<< orphan*/  topology_core_cpumask (scalar_t__) ; 
 int /*<<< orphan*/  zalloc_cpumask_var (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int powernow_k8_cpu_init_acpi(struct powernow_k8_data *data)
{
	struct cpufreq_frequency_table *powernow_table;
	int ret_val = -ENODEV;
	u64 control, status;

	if (acpi_processor_register_performance(&data->acpi_data, data->cpu)) {
		pr_debug("register performance failed: bad ACPI data\n");
		return -EIO;
	}

	/* verify the data contained in the ACPI structures */
	if (data->acpi_data.state_count <= 1) {
		pr_debug("No ACPI P-States\n");
		goto err_out;
	}

	control = data->acpi_data.control_register.space_id;
	status = data->acpi_data.status_register.space_id;

	if ((control != ACPI_ADR_SPACE_FIXED_HARDWARE) ||
	    (status != ACPI_ADR_SPACE_FIXED_HARDWARE)) {
		pr_debug("Invalid control/status registers (%llx - %llx)\n",
			control, status);
		goto err_out;
	}

	/* fill in data->powernow_table */
	powernow_table = kzalloc((sizeof(*powernow_table)
		* (data->acpi_data.state_count + 1)), GFP_KERNEL);
	if (!powernow_table)
		goto err_out;

	/* fill in data */
	data->numps = data->acpi_data.state_count;
	powernow_k8_acpi_pst_values(data, 0);

	ret_val = fill_powernow_table_fidvid(data, powernow_table);
	if (ret_val)
		goto err_out_mem;

	powernow_table[data->acpi_data.state_count].frequency =
		CPUFREQ_TABLE_END;
	data->powernow_table = powernow_table;

	if (cpumask_first(topology_core_cpumask(data->cpu)) == data->cpu)
		print_basics(data);

	/* notify BIOS that we exist */
	acpi_processor_notify_smm(THIS_MODULE);

	if (!zalloc_cpumask_var(&data->acpi_data.shared_cpu_map, GFP_KERNEL)) {
		pr_err("unable to alloc powernow_k8_data cpumask\n");
		ret_val = -ENOMEM;
		goto err_out_mem;
	}

	return 0;

err_out_mem:
	kfree(powernow_table);

err_out:
	acpi_processor_unregister_performance(data->cpu);

	/* data->acpi_data.state_count informs us at ->exit()
	 * whether ACPI was used */
	data->acpi_data.state_count = 0;

	return ret_val;
}