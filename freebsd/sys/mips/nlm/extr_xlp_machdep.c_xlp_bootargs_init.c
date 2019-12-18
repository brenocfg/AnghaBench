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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  buf ;
typedef  int __register_t ;

/* Variables and functions */
 int /*<<< orphan*/  boot_parse_cmdline (char*) ; 
 int /*<<< orphan*/  boothowto ; 
 int /*<<< orphan*/  freeenv (char*) ; 
 scalar_t__ getenv_uint (char*,int*) ; 
 char* kern_getenv (char*) ; 
 int /*<<< orphan*/  kern_setenv (char*,char*) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int) ; 
 scalar_t__ strlen (char*) ; 
 char* strsep (char**,char*) ; 
 int xlp_hw_thread_mask ; 

__attribute__((used)) static void
xlp_bootargs_init(__register_t arg)
{
	char	buf[2048]; /* early stack is big enough */
	char	*p, *v, *n;
	uint32_t mask;

	/*
	 * provide backward compat for passing cpu mask as arg
	 */
	if (arg & 1) {
		xlp_hw_thread_mask = arg;
		return;
	}

	p = (void *)(intptr_t)arg;
	while (*p != '\0') {
		strlcpy(buf, p, sizeof(buf));
		v = buf;
		n = strsep(&v, "=");
		if (v == NULL)
			kern_setenv(n, "1");
		else
			kern_setenv(n, v);
		p += strlen(p) + 1;
	}

	/* CPU mask can be passed thru env */
	if (getenv_uint("cpumask", &mask) != 0)
		xlp_hw_thread_mask = mask;

	/* command line argument */
	v = kern_getenv("bootargs");
	if (v != NULL) {
		strlcpy(buf, v, sizeof(buf));
		boothowto |= boot_parse_cmdline(buf);
		freeenv(v);
	}
}