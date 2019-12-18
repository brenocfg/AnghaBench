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
struct pmc_event_descr {char* pm_ev_name; } ;
typedef  enum pmc_class { ____Placeholder_pmc_class } pmc_class ;
struct TYPE_4__ {int /*<<< orphan*/  pm_cputype; } ;
struct TYPE_3__ {int pm_nevent; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
#define  PMC_CLASS_ARMV7 145 
#define  PMC_CLASS_ARMV8 144 
#define  PMC_CLASS_BERI 143 
#define  PMC_CLASS_E500 142 
#define  PMC_CLASS_IAF 141 
#define  PMC_CLASS_K8 140 
#define  PMC_CLASS_MIPS24K 139 
#define  PMC_CLASS_MIPS74K 138 
#define  PMC_CLASS_OCTEON 137 
#define  PMC_CLASS_PPC7450 136 
#define  PMC_CLASS_PPC970 135 
#define  PMC_CLASS_SOFT 134 
#define  PMC_CLASS_TSC 133 
#define  PMC_CLASS_XSCALE 132 
#define  PMC_CPU_ARMV7_CORTEX_A8 131 
#define  PMC_CPU_ARMV7_CORTEX_A9 130 
#define  PMC_CPU_ARMV8_CORTEX_A53 129 
#define  PMC_CPU_ARMV8_CORTEX_A57 128 
 int PMC_EVENT_TABLE_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  beri ; 
 struct pmc_event_descr* beri_event_table ; 
 int /*<<< orphan*/  cortex_a53 ; 
 struct pmc_event_descr* cortex_a53_event_table ; 
 int /*<<< orphan*/  cortex_a57 ; 
 struct pmc_event_descr* cortex_a57_event_table ; 
 int /*<<< orphan*/  cortex_a8 ; 
 struct pmc_event_descr* cortex_a8_event_table ; 
 int /*<<< orphan*/  cortex_a9 ; 
 struct pmc_event_descr* cortex_a9_event_table ; 
 TYPE_2__ cpu_info ; 
 int /*<<< orphan*/  e500 ; 
 struct pmc_event_descr* e500_event_table ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  iaf ; 
 struct pmc_event_descr* iaf_event_table ; 
 int /*<<< orphan*/  k8 ; 
 struct pmc_event_descr* k8_event_table ; 
 char** malloc (int) ; 
 int /*<<< orphan*/  mips24k ; 
 struct pmc_event_descr* mips24k_event_table ; 
 int /*<<< orphan*/  mips74k ; 
 struct pmc_event_descr* mips74k_event_table ; 
 int /*<<< orphan*/  octeon ; 
 struct pmc_event_descr* octeon_event_table ; 
 int /*<<< orphan*/  ppc7450 ; 
 struct pmc_event_descr* ppc7450_event_table ; 
 int /*<<< orphan*/  ppc970 ; 
 struct pmc_event_descr* ppc970_event_table ; 
 TYPE_1__ soft_event_info ; 
 struct pmc_event_descr* soft_event_table ; 
 int /*<<< orphan*/  tsc ; 
 struct pmc_event_descr* tsc_event_table ; 
 int /*<<< orphan*/  xscale ; 
 struct pmc_event_descr* xscale_event_table ; 

int
pmc_event_names_of_class(enum pmc_class cl, const char ***eventnames,
    int *nevents)
{
	int count;
	const char **names;
	const struct pmc_event_descr *ev;

	switch (cl)
	{
	case PMC_CLASS_IAF:
		ev = iaf_event_table;
		count = PMC_EVENT_TABLE_SIZE(iaf);
		break;
	case PMC_CLASS_TSC:
		ev = tsc_event_table;
		count = PMC_EVENT_TABLE_SIZE(tsc);
		break;
	case PMC_CLASS_K8:
		ev = k8_event_table;
		count = PMC_EVENT_TABLE_SIZE(k8);
		break;
	case PMC_CLASS_XSCALE:
		ev = xscale_event_table;
		count = PMC_EVENT_TABLE_SIZE(xscale);
		break;
	case PMC_CLASS_ARMV7:
		switch (cpu_info.pm_cputype) {
		default:
		case PMC_CPU_ARMV7_CORTEX_A8:
			ev = cortex_a8_event_table;
			count = PMC_EVENT_TABLE_SIZE(cortex_a8);
			break;
		case PMC_CPU_ARMV7_CORTEX_A9:
			ev = cortex_a9_event_table;
			count = PMC_EVENT_TABLE_SIZE(cortex_a9);
			break;
		}
		break;
	case PMC_CLASS_ARMV8:
		switch (cpu_info.pm_cputype) {
		default:
		case PMC_CPU_ARMV8_CORTEX_A53:
			ev = cortex_a53_event_table;
			count = PMC_EVENT_TABLE_SIZE(cortex_a53);
			break;
		case PMC_CPU_ARMV8_CORTEX_A57:
			ev = cortex_a57_event_table;
			count = PMC_EVENT_TABLE_SIZE(cortex_a57);
			break;
		}
		break;
	case PMC_CLASS_BERI:
		ev = beri_event_table;
		count = PMC_EVENT_TABLE_SIZE(beri);
		break;
	case PMC_CLASS_MIPS24K:
		ev = mips24k_event_table;
		count = PMC_EVENT_TABLE_SIZE(mips24k);
		break;
	case PMC_CLASS_MIPS74K:
		ev = mips74k_event_table;
		count = PMC_EVENT_TABLE_SIZE(mips74k);
		break;
	case PMC_CLASS_OCTEON:
		ev = octeon_event_table;
		count = PMC_EVENT_TABLE_SIZE(octeon);
		break;
	case PMC_CLASS_PPC7450:
		ev = ppc7450_event_table;
		count = PMC_EVENT_TABLE_SIZE(ppc7450);
		break;
	case PMC_CLASS_PPC970:
		ev = ppc970_event_table;
		count = PMC_EVENT_TABLE_SIZE(ppc970);
		break;
	case PMC_CLASS_E500:
		ev = e500_event_table;
		count = PMC_EVENT_TABLE_SIZE(e500);
		break;
	case PMC_CLASS_SOFT:
		ev = soft_event_table;
		count = soft_event_info.pm_nevent;
		break;
	default:
		errno = EINVAL;
		return (-1);
	}

	if ((names = malloc(count * sizeof(const char *))) == NULL)
		return (-1);

	*eventnames = names;
	*nevents = count;

	for (;count--; ev++, names++)
		*names = ev->pm_ev_name;

	return (0);
}