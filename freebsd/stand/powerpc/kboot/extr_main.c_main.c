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
struct TYPE_2__ {int /*<<< orphan*/  arch_kexec_kseg_get; int /*<<< orphan*/  arch_loadaddr; int /*<<< orphan*/  arch_autoload; int /*<<< orphan*/  arch_readin; int /*<<< orphan*/  arch_copyout; int /*<<< orphan*/  arch_copyin; int /*<<< orphan*/  arch_getdev; } ;

/* Variables and functions */
 TYPE_1__ archsw ; 
 char* bootprog_info ; 
 int /*<<< orphan*/  cons_probe () ; 
 void* host_getmem (size_t const) ; 
 int /*<<< orphan*/  interact () ; 
 int /*<<< orphan*/  kboot_autoload ; 
 int /*<<< orphan*/  kboot_copyin ; 
 int /*<<< orphan*/  kboot_copyout ; 
 int /*<<< orphan*/  kboot_getdev ; 
 int /*<<< orphan*/  kboot_kseg_get ; 
 int /*<<< orphan*/  kboot_loadaddr ; 
 int /*<<< orphan*/  kboot_readin ; 
 int /*<<< orphan*/  printf (char*,char const*) ; 
 int /*<<< orphan*/  setenv (char*,char const*,int) ; 
 int /*<<< orphan*/  setheap (void*,void*) ; 

int
main(int argc, const char **argv)
{
	void *heapbase;
	const size_t heapsize = 15*1024*1024;
	const char *bootdev;

	/*
	 * Set the heap to one page after the end of the loader.
	 */
	heapbase = host_getmem(heapsize);
	setheap(heapbase, heapbase + heapsize);

	/*
	 * Set up console.
	 */
	cons_probe();

	/* Choose bootdev if provided */
	if (argc > 1)
		bootdev = argv[1];
	else
		bootdev = "";

	printf("Boot device: %s\n", bootdev);

	archsw.arch_getdev = kboot_getdev;
	archsw.arch_copyin = kboot_copyin;
	archsw.arch_copyout = kboot_copyout;
	archsw.arch_readin = kboot_readin;
	archsw.arch_autoload = kboot_autoload;
	archsw.arch_loadaddr = kboot_loadaddr;
	archsw.arch_kexec_kseg_get = kboot_kseg_get;

	printf("\n%s", bootprog_info);

	setenv("currdev", bootdev, 1);
	setenv("loaddev", bootdev, 1);
	setenv("LINES", "24", 1);
	setenv("usefdt", "1", 1);

	interact();			/* doesn't return */

	return (0);
}