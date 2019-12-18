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
struct term_info {char* ti_name; char* ti_desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONS_SETTERM ; 
 int /*<<< orphan*/  get_terminal_emulator (int /*<<< orphan*/ ,struct term_info*) ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct term_info*) ; 
 int /*<<< orphan*/  printf (char*,char*,char*,char*,char*) ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,int) ; 
 int /*<<< orphan*/  warn (char*,char const*) ; 

__attribute__((used)) static void
set_terminal_emulator(const char *name)
{
	struct term_info old_ti, ti;

	get_terminal_emulator(0, &old_ti);
	strlcpy((char *)ti.ti_name, name, sizeof(ti.ti_name));
	if (ioctl(0, CONS_SETTERM, &ti) != 0)
		warn("SETTERM '%s'", name);
	get_terminal_emulator(0, &ti);
	printf("%s (%s) -> %s (%s)\n", old_ti.ti_name, old_ti.ti_desc,
	    ti.ti_name, ti.ti_desc);
}