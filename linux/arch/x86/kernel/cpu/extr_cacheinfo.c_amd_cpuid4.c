#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
union l3_cache {size_t assoc; unsigned int line_size; unsigned int lines_per_tag; int size_encoded; int /*<<< orphan*/  val; } ;
union l2_cache {size_t assoc; unsigned int line_size; unsigned int lines_per_tag; int /*<<< orphan*/  val; } ;
union l1_cache {size_t assoc; unsigned int line_size; unsigned int lines_per_tag; unsigned int size_in_kb; int /*<<< orphan*/  val; } ;
struct TYPE_6__ {unsigned int number_of_sets; } ;
union _cpuid4_leaf_ecx {TYPE_2__ split; scalar_t__ full; } ;
struct TYPE_7__ {unsigned int coherency_line_size; unsigned int ways_of_associativity; unsigned int physical_line_partition; } ;
union _cpuid4_leaf_ebx {TYPE_3__ split; scalar_t__ full; } ;
struct TYPE_5__ {int is_self_initializing; int is_fully_associative; void* num_cores_on_die; scalar_t__ num_threads_sharing; int /*<<< orphan*/  level; int /*<<< orphan*/  type; } ;
union _cpuid4_leaf_eax {TYPE_1__ split; scalar_t__ full; } ;
struct TYPE_8__ {int /*<<< orphan*/  x86_max_cores; int /*<<< orphan*/  x86_cache_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  X86_FEATURE_AMD_DCM ; 
 void* __this_cpu_read (int /*<<< orphan*/ ) ; 
 unsigned int* assocs ; 
 int /*<<< orphan*/  boot_cpu_has (int /*<<< orphan*/ ) ; 
 TYPE_4__ cpu_info ; 
 int /*<<< orphan*/  cpuid (int,unsigned int*,unsigned int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * levels ; 
 int /*<<< orphan*/ * types ; 

__attribute__((used)) static void
amd_cpuid4(int leaf, union _cpuid4_leaf_eax *eax,
		     union _cpuid4_leaf_ebx *ebx,
		     union _cpuid4_leaf_ecx *ecx)
{
	unsigned dummy;
	unsigned line_size, lines_per_tag, assoc, size_in_kb;
	union l1_cache l1i, l1d;
	union l2_cache l2;
	union l3_cache l3;
	union l1_cache *l1 = &l1d;

	eax->full = 0;
	ebx->full = 0;
	ecx->full = 0;

	cpuid(0x80000005, &dummy, &dummy, &l1d.val, &l1i.val);
	cpuid(0x80000006, &dummy, &dummy, &l2.val, &l3.val);

	switch (leaf) {
	case 1:
		l1 = &l1i;
		/* fall through */
	case 0:
		if (!l1->val)
			return;
		assoc = assocs[l1->assoc];
		line_size = l1->line_size;
		lines_per_tag = l1->lines_per_tag;
		size_in_kb = l1->size_in_kb;
		break;
	case 2:
		if (!l2.val)
			return;
		assoc = assocs[l2.assoc];
		line_size = l2.line_size;
		lines_per_tag = l2.lines_per_tag;
		/* cpu_data has errata corrections for K7 applied */
		size_in_kb = __this_cpu_read(cpu_info.x86_cache_size);
		break;
	case 3:
		if (!l3.val)
			return;
		assoc = assocs[l3.assoc];
		line_size = l3.line_size;
		lines_per_tag = l3.lines_per_tag;
		size_in_kb = l3.size_encoded * 512;
		if (boot_cpu_has(X86_FEATURE_AMD_DCM)) {
			size_in_kb = size_in_kb >> 1;
			assoc = assoc >> 1;
		}
		break;
	default:
		return;
	}

	eax->split.is_self_initializing = 1;
	eax->split.type = types[leaf];
	eax->split.level = levels[leaf];
	eax->split.num_threads_sharing = 0;
	eax->split.num_cores_on_die = __this_cpu_read(cpu_info.x86_max_cores) - 1;


	if (assoc == 0xffff)
		eax->split.is_fully_associative = 1;
	ebx->split.coherency_line_size = line_size - 1;
	ebx->split.ways_of_associativity = assoc - 1;
	ebx->split.physical_line_partition = lines_per_tag - 1;
	ecx->split.number_of_sets = (size_in_kb * 1024) / line_size /
		(ebx->split.ways_of_associativity + 1) - 1;
}