#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct x86_topo_layer   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  topo_layers ;
struct topo_node {int dummy; } ;
struct x86_topo_layer {int type; int subtype; int id_shift; } ;
struct TYPE_5__ {void* id_shift; scalar_t__ present; } ;
struct TYPE_4__ {int /*<<< orphan*/  cpu_present; } ;

/* Variables and functions */
 scalar_t__ CPU_VENDOR_AMD ; 
 scalar_t__ CPU_VENDOR_INTEL ; 
 int /*<<< orphan*/  CPU_ZERO (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int MAX_CACHE_LEVELS ; 
 int TOPO_TYPE_CACHE ; 
 int TOPO_TYPE_CORE ; 
 int TOPO_TYPE_GROUP ; 
 int TOPO_TYPE_PKG ; 
 int TOPO_TYPE_PU ; 
 int boot_cpu_id ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  bzero (TYPE_3__*,int) ; 
 TYPE_2__* caches ; 
 void* core_id_shift ; 
 TYPE_1__* cpu_info ; 
 scalar_t__ cpu_vendor_id ; 
 int /*<<< orphan*/  logical_cpus_mask ; 
 int max_apic_id ; 
 int mp_ncpus ; 
 void* node_id_shift ; 
 void* pkg_id_shift ; 
 int /*<<< orphan*/  printf (char*,int,...) ; 
 struct topo_node* topo_add_node_by_hwid (struct topo_node*,int,int,int) ; 
 struct topo_node* topo_find_node_by_hwid (struct topo_node*,int,int,int) ; 
 int /*<<< orphan*/  topo_init_root (struct topo_node*) ; 
 int /*<<< orphan*/  topo_probe_amd () ; 
 int /*<<< orphan*/  topo_probe_intel () ; 
 int /*<<< orphan*/  topo_promote_child (struct topo_node*) ; 
 struct topo_node topo_root ; 

void
topo_probe(void)
{
	static int cpu_topo_probed = 0;
	struct x86_topo_layer {
		int type;
		int subtype;
		int id_shift;
	} topo_layers[MAX_CACHE_LEVELS + 4];
	struct topo_node *parent;
	struct topo_node *node;
	int layer;
	int nlayers;
	int node_id;
	int i;

	if (cpu_topo_probed)
		return;

	CPU_ZERO(&logical_cpus_mask);

	if (mp_ncpus <= 1)
		; /* nothing */
	else if (cpu_vendor_id == CPU_VENDOR_AMD)
		topo_probe_amd();
	else if (cpu_vendor_id == CPU_VENDOR_INTEL)
		topo_probe_intel();

	KASSERT(pkg_id_shift >= core_id_shift,
	    ("bug in APIC topology discovery"));

	nlayers = 0;
	bzero(topo_layers, sizeof(topo_layers));

	topo_layers[nlayers].type = TOPO_TYPE_PKG;
	topo_layers[nlayers].id_shift = pkg_id_shift;
	if (bootverbose)
		printf("Package ID shift: %u\n", topo_layers[nlayers].id_shift);
	nlayers++;

	if (pkg_id_shift > node_id_shift && node_id_shift != 0) {
		topo_layers[nlayers].type = TOPO_TYPE_GROUP;
		topo_layers[nlayers].id_shift = node_id_shift;
		if (bootverbose)
			printf("Node ID shift: %u\n",
			    topo_layers[nlayers].id_shift);
		nlayers++;
	}

	/*
	 * Consider all caches to be within a package/chip
	 * and "in front" of all sub-components like
	 * cores and hardware threads.
	 */
	for (i = MAX_CACHE_LEVELS - 1; i >= 0; --i) {
		if (caches[i].present) {
			if (node_id_shift != 0)
				KASSERT(caches[i].id_shift <= node_id_shift,
					("bug in APIC topology discovery"));
			KASSERT(caches[i].id_shift <= pkg_id_shift,
				("bug in APIC topology discovery"));
			KASSERT(caches[i].id_shift >= core_id_shift,
				("bug in APIC topology discovery"));

			topo_layers[nlayers].type = TOPO_TYPE_CACHE;
			topo_layers[nlayers].subtype = i + 1;
			topo_layers[nlayers].id_shift = caches[i].id_shift;
			if (bootverbose)
				printf("L%u cache ID shift: %u\n",
				    topo_layers[nlayers].subtype,
				    topo_layers[nlayers].id_shift);
			nlayers++;
		}
	}

	if (pkg_id_shift > core_id_shift) {
		topo_layers[nlayers].type = TOPO_TYPE_CORE;
		topo_layers[nlayers].id_shift = core_id_shift;
		if (bootverbose)
			printf("Core ID shift: %u\n",
			    topo_layers[nlayers].id_shift);
		nlayers++;
	}

	topo_layers[nlayers].type = TOPO_TYPE_PU;
	topo_layers[nlayers].id_shift = 0;
	nlayers++;

	topo_init_root(&topo_root);
	for (i = 0; i <= max_apic_id; ++i) {
		if (!cpu_info[i].cpu_present)
			continue;

		parent = &topo_root;
		for (layer = 0; layer < nlayers; ++layer) {
			node_id = i >> topo_layers[layer].id_shift;
			parent = topo_add_node_by_hwid(parent, node_id,
			    topo_layers[layer].type,
			    topo_layers[layer].subtype);
		}
	}

	parent = &topo_root;
	for (layer = 0; layer < nlayers; ++layer) {
		node_id = boot_cpu_id >> topo_layers[layer].id_shift;
		node = topo_find_node_by_hwid(parent, node_id,
		    topo_layers[layer].type,
		    topo_layers[layer].subtype);
		topo_promote_child(node);
		parent = node;
	}

	cpu_topo_probed = 1;
}