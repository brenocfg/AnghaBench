#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_8__ {int transition_latency; } ;
struct cpufreq_policy {unsigned int cpu; struct cpufreq_frequency_table* freq_table; TYPE_3__ cpuinfo; } ;
struct cpufreq_frequency_table {int frequency; } ;
struct TYPE_7__ {scalar_t__ space_id; } ;
struct TYPE_6__ {scalar_t__ space_id; } ;
struct TYPE_10__ {int state_count; unsigned int state; TYPE_4__* states; TYPE_2__ status_register; TYPE_1__ control_register; } ;
struct cpufreq_acpi_io {int resume; TYPE_5__ acpi_data; } ;
struct TYPE_9__ {int transition_latency; int core_frequency; scalar_t__ control; scalar_t__ status; scalar_t__ bus_master_latency; scalar_t__ power; } ;

/* Variables and functions */
 scalar_t__ ACPI_ADR_SPACE_FIXED_HARDWARE ; 
 int CPUFREQ_TABLE_END ; 
 unsigned int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 struct cpufreq_acpi_io** acpi_io_data ; 
 int /*<<< orphan*/  acpi_processor_notify_smm (int /*<<< orphan*/ ) ; 
 unsigned int acpi_processor_register_performance (TYPE_5__*,unsigned int) ; 
 int /*<<< orphan*/  acpi_processor_unregister_performance (unsigned int) ; 
 struct cpufreq_frequency_table* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct cpufreq_acpi_io*) ; 
 struct cpufreq_acpi_io* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 int /*<<< orphan*/  pr_info (char*,unsigned int) ; 

__attribute__((used)) static int
acpi_cpufreq_cpu_init (
	struct cpufreq_policy   *policy)
{
	unsigned int		i;
	unsigned int		cpu = policy->cpu;
	struct cpufreq_acpi_io	*data;
	unsigned int		result = 0;
	struct cpufreq_frequency_table *freq_table;

	pr_debug("acpi_cpufreq_cpu_init\n");

	data = kzalloc(sizeof(*data), GFP_KERNEL);
	if (!data)
		return (-ENOMEM);

	acpi_io_data[cpu] = data;

	result = acpi_processor_register_performance(&data->acpi_data, cpu);

	if (result)
		goto err_free;

	/* capability check */
	if (data->acpi_data.state_count <= 1) {
		pr_debug("No P-States\n");
		result = -ENODEV;
		goto err_unreg;
	}

	if ((data->acpi_data.control_register.space_id !=
					ACPI_ADR_SPACE_FIXED_HARDWARE) ||
	    (data->acpi_data.status_register.space_id !=
					ACPI_ADR_SPACE_FIXED_HARDWARE)) {
		pr_debug("Unsupported address space [%d, %d]\n",
			(u32) (data->acpi_data.control_register.space_id),
			(u32) (data->acpi_data.status_register.space_id));
		result = -ENODEV;
		goto err_unreg;
	}

	/* alloc freq_table */
	freq_table = kcalloc(data->acpi_data.state_count + 1,
	                           sizeof(*freq_table),
	                           GFP_KERNEL);
	if (!freq_table) {
		result = -ENOMEM;
		goto err_unreg;
	}

	/* detect transition latency */
	policy->cpuinfo.transition_latency = 0;
	for (i=0; i<data->acpi_data.state_count; i++) {
		if ((data->acpi_data.states[i].transition_latency * 1000) >
		    policy->cpuinfo.transition_latency) {
			policy->cpuinfo.transition_latency =
			    data->acpi_data.states[i].transition_latency * 1000;
		}
	}

	/* table init */
	for (i = 0; i <= data->acpi_data.state_count; i++)
	{
		if (i < data->acpi_data.state_count) {
			freq_table[i].frequency =
			      data->acpi_data.states[i].core_frequency * 1000;
		} else {
			freq_table[i].frequency = CPUFREQ_TABLE_END;
		}
	}

	policy->freq_table = freq_table;

	/* notify BIOS that we exist */
	acpi_processor_notify_smm(THIS_MODULE);

	pr_info("CPU%u - ACPI performance management activated\n", cpu);

	for (i = 0; i < data->acpi_data.state_count; i++)
		pr_debug("     %cP%d: %d MHz, %d mW, %d uS, %d uS, 0x%x 0x%x\n",
			(i == data->acpi_data.state?'*':' '), i,
			(u32) data->acpi_data.states[i].core_frequency,
			(u32) data->acpi_data.states[i].power,
			(u32) data->acpi_data.states[i].transition_latency,
			(u32) data->acpi_data.states[i].bus_master_latency,
			(u32) data->acpi_data.states[i].status,
			(u32) data->acpi_data.states[i].control);

	/* the first call to ->target() should result in us actually
	 * writing something to the appropriate registers. */
	data->resume = 1;

	return (result);

 err_unreg:
	acpi_processor_unregister_performance(cpu);
 err_free:
	kfree(data);
	acpi_io_data[cpu] = NULL;

	return (result);
}