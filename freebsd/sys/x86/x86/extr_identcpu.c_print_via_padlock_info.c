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
typedef  int /*<<< orphan*/  u_int ;

/* Variables and functions */
 int /*<<< orphan*/  do_cpuid (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
print_via_padlock_info(void)
{
	u_int regs[4];

	do_cpuid(0xc0000001, regs);
	printf("\n  VIA Padlock Features=0x%b", regs[3],
	"\020"
	"\003RNG"		/* RNG */
	"\007AES"		/* ACE */
	"\011AES-CTR"		/* ACE2 */
	"\013SHA1,SHA256"	/* PHE */
	"\015RSA"		/* PMM */
	);
}