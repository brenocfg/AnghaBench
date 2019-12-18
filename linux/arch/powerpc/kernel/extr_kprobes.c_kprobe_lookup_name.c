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
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  kprobe_opcode_t ;

/* Variables and functions */
 int KSYM_NAME_LEN ; 
 int /*<<< orphan*/  MODULE_NAME_LEN ; 
 unsigned long ftrace_location_range (unsigned long,unsigned long) ; 
 scalar_t__ kallsyms_lookup_name (char const*) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 scalar_t__ ppc_function_entry (int /*<<< orphan*/ *) ; 
 char* strnchr (char const*,int /*<<< orphan*/ ,char) ; 
 scalar_t__ strscpy (char*,char const*,int) ; 

kprobe_opcode_t *kprobe_lookup_name(const char *name, unsigned int offset)
{
	kprobe_opcode_t *addr = NULL;

#ifdef PPC64_ELF_ABI_v2
	/* PPC64 ABIv2 needs local entry point */
	addr = (kprobe_opcode_t *)kallsyms_lookup_name(name);
	if (addr && !offset) {
#ifdef CONFIG_KPROBES_ON_FTRACE
		unsigned long faddr;
		/*
		 * Per livepatch.h, ftrace location is always within the first
		 * 16 bytes of a function on powerpc with -mprofile-kernel.
		 */
		faddr = ftrace_location_range((unsigned long)addr,
					      (unsigned long)addr + 16);
		if (faddr)
			addr = (kprobe_opcode_t *)faddr;
		else
#endif
			addr = (kprobe_opcode_t *)ppc_function_entry(addr);
	}
#elif defined(PPC64_ELF_ABI_v1)
	/*
	 * 64bit powerpc ABIv1 uses function descriptors:
	 * - Check for the dot variant of the symbol first.
	 * - If that fails, try looking up the symbol provided.
	 *
	 * This ensures we always get to the actual symbol and not
	 * the descriptor.
	 *
	 * Also handle <module:symbol> format.
	 */
	char dot_name[MODULE_NAME_LEN + 1 + KSYM_NAME_LEN];
	bool dot_appended = false;
	const char *c;
	ssize_t ret = 0;
	int len = 0;

	if ((c = strnchr(name, MODULE_NAME_LEN, ':')) != NULL) {
		c++;
		len = c - name;
		memcpy(dot_name, name, len);
	} else
		c = name;

	if (*c != '\0' && *c != '.') {
		dot_name[len++] = '.';
		dot_appended = true;
	}
	ret = strscpy(dot_name + len, c, KSYM_NAME_LEN);
	if (ret > 0)
		addr = (kprobe_opcode_t *)kallsyms_lookup_name(dot_name);

	/* Fallback to the original non-dot symbol lookup */
	if (!addr && dot_appended)
		addr = (kprobe_opcode_t *)kallsyms_lookup_name(name);
#else
	addr = (kprobe_opcode_t *)kallsyms_lookup_name(name);
#endif

	return addr;
}