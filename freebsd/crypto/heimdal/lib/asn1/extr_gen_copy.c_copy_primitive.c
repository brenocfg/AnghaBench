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
 int /*<<< orphan*/  codefile ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,char const*,char const*) ; 
 int /*<<< orphan*/  used_fail ; 

__attribute__((used)) static void
copy_primitive (const char *typename, const char *from, const char *to)
{
    fprintf (codefile, "if(der_copy_%s(%s, %s)) goto fail;\n",
	     typename, from, to);
    used_fail++;
}