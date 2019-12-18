#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct pstate_idx_revmap_data {unsigned int pstate_id; int cpufreq_table_idx; int /*<<< orphan*/  hentry; } ;
struct device_node {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_4__ {scalar_t__ frequency; int /*<<< orphan*/  flags; scalar_t__ driver_data; } ;
struct TYPE_3__ {int wof_enabled; int nr_pstates; int max; int nominal; int min; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPUFREQ_BOOST_FREQ ; 
 scalar_t__ CPUFREQ_TABLE_END ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned int POWERNV_MAX_PSTATES ; 
 scalar_t__ be32_to_cpu (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  hash_add (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned int) ; 
 struct pstate_idx_revmap_data* kmalloc (int,int /*<<< orphan*/ ) ; 
 int min (scalar_t__,scalar_t__) ; 
 struct device_node* of_find_node_by_path (char*) ; 
 int /*<<< orphan*/ * of_get_property (struct device_node*,char*,scalar_t__*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 scalar_t__ of_property_read_u32 (struct device_node*,char*,scalar_t__*) ; 
 TYPE_2__* powernv_freqs ; 
 TYPE_1__ powernv_pstate_info ; 
 int /*<<< orphan*/  pr_debug (char*,scalar_t__,...) ; 
 int /*<<< orphan*/  pr_info (char*,char*,...) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 int /*<<< orphan*/  pstate_revmap ; 

__attribute__((used)) static int init_powernv_pstates(void)
{
	struct device_node *power_mgt;
	int i, nr_pstates = 0;
	const __be32 *pstate_ids, *pstate_freqs;
	u32 len_ids, len_freqs;
	u32 pstate_min, pstate_max, pstate_nominal;
	u32 pstate_turbo, pstate_ultra_turbo;
	int rc = -ENODEV;

	power_mgt = of_find_node_by_path("/ibm,opal/power-mgt");
	if (!power_mgt) {
		pr_warn("power-mgt node not found\n");
		return -ENODEV;
	}

	if (of_property_read_u32(power_mgt, "ibm,pstate-min", &pstate_min)) {
		pr_warn("ibm,pstate-min node not found\n");
		goto out;
	}

	if (of_property_read_u32(power_mgt, "ibm,pstate-max", &pstate_max)) {
		pr_warn("ibm,pstate-max node not found\n");
		goto out;
	}

	if (of_property_read_u32(power_mgt, "ibm,pstate-nominal",
				 &pstate_nominal)) {
		pr_warn("ibm,pstate-nominal not found\n");
		goto out;
	}

	if (of_property_read_u32(power_mgt, "ibm,pstate-ultra-turbo",
				 &pstate_ultra_turbo)) {
		powernv_pstate_info.wof_enabled = false;
		goto next;
	}

	if (of_property_read_u32(power_mgt, "ibm,pstate-turbo",
				 &pstate_turbo)) {
		powernv_pstate_info.wof_enabled = false;
		goto next;
	}

	if (pstate_turbo == pstate_ultra_turbo)
		powernv_pstate_info.wof_enabled = false;
	else
		powernv_pstate_info.wof_enabled = true;

next:
	pr_info("cpufreq pstate min 0x%x nominal 0x%x max 0x%x\n", pstate_min,
		pstate_nominal, pstate_max);
	pr_info("Workload Optimized Frequency is %s in the platform\n",
		(powernv_pstate_info.wof_enabled) ? "enabled" : "disabled");

	pstate_ids = of_get_property(power_mgt, "ibm,pstate-ids", &len_ids);
	if (!pstate_ids) {
		pr_warn("ibm,pstate-ids not found\n");
		goto out;
	}

	pstate_freqs = of_get_property(power_mgt, "ibm,pstate-frequencies-mhz",
				      &len_freqs);
	if (!pstate_freqs) {
		pr_warn("ibm,pstate-frequencies-mhz not found\n");
		goto out;
	}

	if (len_ids != len_freqs) {
		pr_warn("Entries in ibm,pstate-ids and "
			"ibm,pstate-frequencies-mhz does not match\n");
	}

	nr_pstates = min(len_ids, len_freqs) / sizeof(u32);
	if (!nr_pstates) {
		pr_warn("No PStates found\n");
		goto out;
	}

	powernv_pstate_info.nr_pstates = nr_pstates;
	pr_debug("NR PStates %d\n", nr_pstates);

	for (i = 0; i < nr_pstates; i++) {
		u32 id = be32_to_cpu(pstate_ids[i]);
		u32 freq = be32_to_cpu(pstate_freqs[i]);
		struct pstate_idx_revmap_data *revmap_data;
		unsigned int key;

		pr_debug("PState id %d freq %d MHz\n", id, freq);
		powernv_freqs[i].frequency = freq * 1000; /* kHz */
		powernv_freqs[i].driver_data = id & 0xFF;

		revmap_data = kmalloc(sizeof(*revmap_data), GFP_KERNEL);
		if (!revmap_data) {
			rc = -ENOMEM;
			goto out;
		}

		revmap_data->pstate_id = id & 0xFF;
		revmap_data->cpufreq_table_idx = i;
		key = (revmap_data->pstate_id) % POWERNV_MAX_PSTATES;
		hash_add(pstate_revmap, &revmap_data->hentry, key);

		if (id == pstate_max)
			powernv_pstate_info.max = i;
		if (id == pstate_nominal)
			powernv_pstate_info.nominal = i;
		if (id == pstate_min)
			powernv_pstate_info.min = i;

		if (powernv_pstate_info.wof_enabled && id == pstate_turbo) {
			int j;

			for (j = i - 1; j >= (int)powernv_pstate_info.max; j--)
				powernv_freqs[j].flags = CPUFREQ_BOOST_FREQ;
		}
	}

	/* End of list marker entry */
	powernv_freqs[i].frequency = CPUFREQ_TABLE_END;

	of_node_put(power_mgt);
	return 0;
out:
	of_node_put(power_mgt);
	return rc;
}