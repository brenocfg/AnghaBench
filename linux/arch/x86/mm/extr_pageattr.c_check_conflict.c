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
typedef  scalar_t__ pgprotval_t ;
typedef  int /*<<< orphan*/  pgprot_t ;

/* Variables and functions */
#define  CPA_CONFLICT 130 
#define  CPA_DETECT 129 
#define  CPA_PROTECT 128 
 int /*<<< orphan*/  conflicts (int /*<<< orphan*/ ,scalar_t__) ; 
 int cpa_warn_level ; 
 scalar_t__ pgprot_val (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warn (char*,char const*,char const*,unsigned long,unsigned long,unsigned long,unsigned long long,unsigned long long) ; 

__attribute__((used)) static inline void check_conflict(int warnlvl, pgprot_t prot, pgprotval_t val,
				  unsigned long start, unsigned long end,
				  unsigned long pfn, const char *txt)
{
	static const char *lvltxt[] = {
		[CPA_CONFLICT]	= "conflict",
		[CPA_PROTECT]	= "protect",
		[CPA_DETECT]	= "detect",
	};

	if (warnlvl > cpa_warn_level || !conflicts(prot, val))
		return;

	pr_warn("CPA %8s %10s: 0x%016lx - 0x%016lx PFN %lx req %016llx prevent %016llx\n",
		lvltxt[warnlvl], txt, start, end, pfn, (unsigned long long)pgprot_val(prot),
		(unsigned long long)val);
}