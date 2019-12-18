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
struct assignment {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cprint (int,char*,char const*) ; 

__attribute__((used)) static void defval_strings(const char *name, struct assignment *defval)
{
    cprint(1, "opt.%s.num_strings = 0;\n", name);
    cprint(1, "opt.%s.strings = NULL;\n", name);
}