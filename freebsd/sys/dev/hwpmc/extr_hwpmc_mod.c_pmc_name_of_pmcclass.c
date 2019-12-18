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
typedef  enum pmc_class { ____Placeholder_pmc_class } pmc_class ;

/* Variables and functions */
 int /*<<< orphan*/  __PMC_CLASSES () ; 

__attribute__((used)) static const char *
pmc_name_of_pmcclass(enum pmc_class class)
{

	switch (class) {
#undef	__PMC_CLASS
#define	__PMC_CLASS(S,V,D)						\
	case PMC_CLASS_##S:						\
		return #S;
	__PMC_CLASSES();
	default:
		return ("<unknown>");
	}
}