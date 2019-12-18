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
struct TYPE_2__ {int /*<<< orphan*/ * to_sections_end; int /*<<< orphan*/ * to_sections; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLEAR_SOLIB () ; 
 int /*<<< orphan*/  inferior_ptid ; 
 TYPE_1__ kgdb_trgt_ops ; 
 int /*<<< orphan*/ * kvm ; 
 scalar_t__ kvm_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kvm_geterr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  null_ptid ; 
 int /*<<< orphan*/ * vmcore ; 
 int /*<<< orphan*/  warning (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
kgdb_trgt_close(int quitting)
{

	if (kvm != NULL) {		
		inferior_ptid = null_ptid;
		CLEAR_SOLIB();
		if (kvm_close(kvm) != 0)
			warning("cannot close \"%s\": %s", vmcore,
			    kvm_geterr(kvm));
		kvm = NULL;
		xfree(vmcore);
		vmcore = NULL;
		if (kgdb_trgt_ops.to_sections) {
			xfree(kgdb_trgt_ops.to_sections);
			kgdb_trgt_ops.to_sections = NULL;
			kgdb_trgt_ops.to_sections_end = NULL;
		}
	}
}