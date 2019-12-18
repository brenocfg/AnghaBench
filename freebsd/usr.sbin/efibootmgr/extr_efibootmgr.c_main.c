#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  bmgr_opts_t ;
struct TYPE_3__ {char* label; int bootnum; int /*<<< orphan*/  verbose; int /*<<< orphan*/  timeout; scalar_t__ set_timeout; scalar_t__ del_timeout; scalar_t__ delete; scalar_t__ delete_bootnext; scalar_t__ set_bootnext; int /*<<< orphan*/ * order; scalar_t__ set_active; scalar_t__ set_inactive; scalar_t__ has_bootnum; int /*<<< orphan*/  dry_run; int /*<<< orphan*/  env; int /*<<< orphan*/  kernel; int /*<<< orphan*/  loader; scalar_t__ create; } ;

/* Variables and functions */
 int /*<<< orphan*/  del_bootnext () ; 
 int /*<<< orphan*/  delete_bootvar (int) ; 
 int /*<<< orphan*/  delete_timeout () ; 
 int /*<<< orphan*/  efi_variables_supported () ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  handle_activity (int,scalar_t__) ; 
 int /*<<< orphan*/  handle_bootnext (int) ; 
 int /*<<< orphan*/  handle_timeout (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  make_boot_var (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 TYPE_1__ opts ; 
 int /*<<< orphan*/  parse_args (int,char**) ; 
 int /*<<< orphan*/  print_boot_vars (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_vars () ; 
 int /*<<< orphan*/  set_boot_order (int /*<<< orphan*/ *) ; 

int
main(int argc, char *argv[])
{

	if (!efi_variables_supported())
		errx(1, "efi variables not supported on this system. root? kldload efirt?");

	memset(&opts, 0, sizeof (bmgr_opts_t));
	parse_args(argc, argv);
	read_vars();

	if (opts.create)
		/*
		 * side effect, adds to boot order, but not yet active.
		 */
		make_boot_var(opts.label ? opts.label : "",
		    opts.loader, opts.kernel, opts.env, opts.dry_run,
		    opts.has_bootnum ? opts.bootnum : -1, opts.set_active);
	else if (opts.set_active || opts.set_inactive )
		handle_activity(opts.bootnum, opts.set_active);
	else if (opts.order != NULL)
		set_boot_order(opts.order); /* create a new bootorder with opts.order */
	else if (opts.set_bootnext)
		handle_bootnext(opts.bootnum);
	else if (opts.delete_bootnext)
		del_bootnext();
	else if (opts.delete)
		delete_bootvar(opts.bootnum);
	else if (opts.del_timeout)
		delete_timeout();
	else if (opts.set_timeout)
		handle_timeout(opts.timeout);

	print_boot_vars(opts.verbose);
}