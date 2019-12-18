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
struct kthr {int /*<<< orphan*/  tid; } ;
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  PINKERNEL (scalar_t__) ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  error_no_arg (char*) ; 
 int /*<<< orphan*/  kgdb_switch_to_thread (int /*<<< orphan*/ ) ; 
 struct kthr* kgdb_thr_lookup_paddr (scalar_t__) ; 
 struct kthr* kgdb_thr_lookup_pid (int) ; 
 int /*<<< orphan*/ * kvm ; 
 scalar_t__ parse_and_eval_address (char*) ; 

__attribute__((used)) static void
kgdb_set_proc_cmd (char *arg, int from_tty)
{
	CORE_ADDR addr;
	struct kthr *thr;

	if (!arg)
		error_no_arg ("proc address for the new context");

	if (kvm == NULL)
		error ("only supported for core file target");

	addr = (CORE_ADDR) parse_and_eval_address (arg);

	if (!PINKERNEL (addr)) {
		thr = kgdb_thr_lookup_pid((int)addr);
		if (thr == NULL)
			error ("invalid pid");
	} else {
		thr = kgdb_thr_lookup_paddr(addr);
		if (thr == NULL)
			error("invalid proc address");
	}
	kgdb_switch_to_thread(thr->tid);
}