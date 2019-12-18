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
 int /*<<< orphan*/  errx (int,char*) ; 

__attribute__((used)) static void
usage(void)
{

	errx(1, "efivar [-abdDHlLNpRtuw] [-n name] [-f file] [--append] [--ascii]\n"
	    "\t[--attributes] [--binary] [--delete] [--fromfile file] [--hex]\n"
	    "\t[--list-guids] [--list] [--load-option] [--name name] [--no-name]\n"
	    "\t[--print] [--print-decimal] [--raw-guid] [--utf8] [--write]\n"
	    "\tname[=value]");
}