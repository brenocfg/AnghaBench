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
 int /*<<< orphan*/  f_print (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  fout ; 
 int /*<<< orphan*/  tabify (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
print_ifopen(int indent, const char *name)
{
	tabify(fout, indent);
	f_print(fout, "if (!xdr_%s(xdrs", name);
}