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
struct target_ops {int (* to_xfer_memory ) (int /*<<< orphan*/ ,char*,int,int,struct mem_attrib*,struct target_ops*) ;} ;
struct mem_attrib {int dummy; } ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 struct target_ops* find_target_beneath (struct target_ops*) ; 
 int /*<<< orphan*/ * kvm ; 
 int kvm_read2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 
 int kvm_write (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 
 int stub1 (int /*<<< orphan*/ ,char*,int,int,struct mem_attrib*,struct target_ops*) ; 

__attribute__((used)) static int
kgdb_trgt_xfer_memory(CORE_ADDR memaddr, char *myaddr, int len, int write,
    struct mem_attrib *attrib, struct target_ops *target)
{
	struct target_ops *tb;

	if (kvm != NULL) {
		if (len == 0)
			return (0);
		if (!write)
			return (kvm_read2(kvm, memaddr, myaddr, len));
		else
			return (kvm_write(kvm, memaddr, myaddr, len));
	}
	tb = find_target_beneath(target);
	return (tb->to_xfer_memory(memaddr, myaddr, len, write, attrib, tb));
}