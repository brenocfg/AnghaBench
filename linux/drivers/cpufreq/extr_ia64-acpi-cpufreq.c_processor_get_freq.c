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
struct cpufreq_acpi_req {unsigned int cpu; } ;
struct cpufreq_acpi_io {int dummy; } ;

/* Variables and functions */
 long EAGAIN ; 
 struct cpufreq_acpi_io** acpi_io_data ; 
 int extract_clock (struct cpufreq_acpi_io*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  pr_warn (char*,int) ; 
 int processor_get_pstate (int /*<<< orphan*/ *) ; 
 unsigned int smp_processor_id () ; 

__attribute__((used)) static long
processor_get_freq (
	void *arg)
{
	struct cpufreq_acpi_req *req = arg;
	unsigned int		cpu = req->cpu;
	struct cpufreq_acpi_io	*data = acpi_io_data[cpu];
	u32			value;
	int			ret;

	pr_debug("processor_get_freq\n");
	if (smp_processor_id() != cpu)
		return -EAGAIN;

	/* processor_get_pstate gets the instantaneous frequency */
	ret = processor_get_pstate(&value);
	if (ret) {
		pr_warn("get performance failed with error %d\n", ret);
		return ret;
	}
	return 1000 * extract_clock(data, value);
}