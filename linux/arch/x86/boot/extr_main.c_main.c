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

/* Variables and functions */
 scalar_t__ cmdline_find_option_bool (char*) ; 
 int /*<<< orphan*/  console_init () ; 
 int /*<<< orphan*/  copy_boot_params () ; 
 int /*<<< orphan*/  detect_memory () ; 
 int /*<<< orphan*/  die () ; 
 int /*<<< orphan*/  go_to_protected_mode () ; 
 int /*<<< orphan*/  init_heap () ; 
 int /*<<< orphan*/  keyboard_init () ; 
 int /*<<< orphan*/  puts (char*) ; 
 int /*<<< orphan*/  query_apm_bios () ; 
 int /*<<< orphan*/  query_edd () ; 
 int /*<<< orphan*/  query_ist () ; 
 int /*<<< orphan*/  set_bios_mode () ; 
 int /*<<< orphan*/  set_video () ; 
 scalar_t__ validate_cpu () ; 

void main(void)
{
	/* First, copy the boot header into the "zeropage" */
	copy_boot_params();

	/* Initialize the early-boot console */
	console_init();
	if (cmdline_find_option_bool("debug"))
		puts("early console in setup code\n");

	/* End of heap check */
	init_heap();

	/* Make sure we have all the proper CPU support */
	if (validate_cpu()) {
		puts("Unable to boot - please use a kernel appropriate "
		     "for your CPU.\n");
		die();
	}

	/* Tell the BIOS what CPU mode we intend to run in. */
	set_bios_mode();

	/* Detect memory layout */
	detect_memory();

	/* Set keyboard repeat rate (why?) and query the lock flags */
	keyboard_init();

	/* Query Intel SpeedStep (IST) information */
	query_ist();

	/* Query APM information */
#if defined(CONFIG_APM) || defined(CONFIG_APM_MODULE)
	query_apm_bios();
#endif

	/* Query EDD information */
#if defined(CONFIG_EDD) || defined(CONFIG_EDD_MODULE)
	query_edd();
#endif

	/* Set the video mode */
	set_video();

	/* Do the last things and invoke protected mode */
	go_to_protected_mode();
}