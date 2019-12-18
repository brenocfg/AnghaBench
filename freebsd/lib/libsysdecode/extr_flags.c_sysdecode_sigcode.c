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
#define  SIGBUS 133 
#define  SIGCHLD 132 
#define  SIGFPE 131 
#define  SIGILL 130 
#define  SIGSEGV 129 
#define  SIGTRAP 128 
 char* lookup_value (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sigcode ; 
 char const* sysdecode_sigbus_code (int) ; 
 char const* sysdecode_sigchld_code (int) ; 
 char const* sysdecode_sigfpe_code (int) ; 
 char const* sysdecode_sigill_code (int) ; 
 char const* sysdecode_sigsegv_code (int) ; 
 char const* sysdecode_sigtrap_code (int) ; 

const char *
sysdecode_sigcode(int sig, int si_code)
{
	const char *str;

	str = lookup_value(sigcode, si_code);
	if (str != NULL)
		return (str);
	
	switch (sig) {
	case SIGILL:
		return (sysdecode_sigill_code(si_code));
	case SIGBUS:
		return (sysdecode_sigbus_code(si_code));
	case SIGSEGV:
		return (sysdecode_sigsegv_code(si_code));
	case SIGFPE:
		return (sysdecode_sigfpe_code(si_code));
	case SIGTRAP:
		return (sysdecode_sigtrap_code(si_code));
	case SIGCHLD:
		return (sysdecode_sigchld_code(si_code));
	default:
		return (NULL);
	}
}