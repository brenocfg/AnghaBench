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
 int RB_MUTE ; 
 int RB_SERIAL ; 
 int boot_env_to_howto () ; 
 int boot_parse_cmdline (char*) ; 
 int /*<<< orphan*/  getenv (char*) ; 
 int md_bootserial () ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
md_getboothowto(char *kargs)
{
    int		howto;

    /* Parse kargs */
    howto = boot_parse_cmdline(kargs);
    howto |= boot_env_to_howto();
#if defined(__sparc64__)
    if (md_bootserial() != -1)
	howto |= RB_SERIAL;
#else
    if (!strcmp(getenv("console"), "comconsole"))
	howto |= RB_SERIAL;
    if (!strcmp(getenv("console"), "nullconsole"))
	howto |= RB_MUTE;
#endif
    return(howto);
}