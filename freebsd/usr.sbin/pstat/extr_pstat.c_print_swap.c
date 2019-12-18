#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct kvm_swap {double ksw_total; double ksw_used; int /*<<< orphan*/  ksw_devname; } ;
struct TYPE_2__ {double ksw_total; double ksw_used; } ;

/* Variables and functions */
 int /*<<< orphan*/  nswdev ; 
 int /*<<< orphan*/  print_swap_line (int /*<<< orphan*/ ,double,double,double,double) ; 
 TYPE_1__ swtot ; 
 scalar_t__ totalflag ; 

__attribute__((used)) static void
print_swap(struct kvm_swap *ksw)
{

	swtot.ksw_total += ksw->ksw_total;
	swtot.ksw_used += ksw->ksw_used;
	++nswdev;
	if (totalflag == 0)
		print_swap_line(ksw->ksw_devname, ksw->ksw_total,
		    ksw->ksw_used, ksw->ksw_total - ksw->ksw_used,
		    (ksw->ksw_used * 100.0) / ksw->ksw_total);
}