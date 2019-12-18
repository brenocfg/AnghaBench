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
struct consdev {int /*<<< orphan*/  cn_pri; } ;

/* Variables and functions */
 int /*<<< orphan*/  CFE_STDHANDLE_CONSOLE ; 
 int /*<<< orphan*/  CN_DEAD ; 
 int /*<<< orphan*/  CN_LOW ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  cfe_cnputc (struct consdev*,char) ; 
 scalar_t__ cfe_getstdhandle (int /*<<< orphan*/ ) ; 
 scalar_t__ conhandle ; 
 int strlen (char*) ; 

__attribute__((used)) static void
cfe_cnprobe(struct consdev *cp)
{

	conhandle = cfe_getstdhandle(CFE_STDHANDLE_CONSOLE);
	if (conhandle < 0) {
		cp->cn_pri = CN_DEAD;
		return;
	}

	/* XXX */
	if (bootverbose) {
		char *bootmsg = "Using CFE firmware console.\n";
		int i;

		for (i = 0; i < strlen(bootmsg); i++)
			cfe_cnputc(cp, bootmsg[i]);
	}

	cp->cn_pri = CN_LOW;
}