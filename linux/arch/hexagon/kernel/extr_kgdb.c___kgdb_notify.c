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
struct die_args {int trapnr; int /*<<< orphan*/  regs; int /*<<< orphan*/  err; int /*<<< orphan*/  signr; } ;

/* Variables and functions */
 int NOTIFY_DONE ; 
 int NOTIFY_STOP ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kgdb_active ; 
 scalar_t__ kgdb_handle_exception (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kgdb_nmicallback (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_processor_id () ; 
 scalar_t__ user_mode (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __kgdb_notify(struct die_args *args, unsigned long cmd)
{
	/* cpu roundup */
	if (atomic_read(&kgdb_active) != -1) {
		kgdb_nmicallback(smp_processor_id(), args->regs);
		return NOTIFY_STOP;
	}

	if (user_mode(args->regs))
		return NOTIFY_DONE;

	if (kgdb_handle_exception(args->trapnr & 0xff, args->signr, args->err,
				    args->regs))
		return NOTIFY_DONE;

	return NOTIFY_STOP;
}