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
 int /*<<< orphan*/  f_print (int /*<<< orphan*/ ,char*,char const*,char const*,char const*,char const*,char const*) ; 
 int /*<<< orphan*/  fout ; 

__attribute__((used)) static void
printif(const char *proc, const char *transp, const char *prefix,
    const char *arg)
{
	f_print(fout, "\tif (!svc_%s(%s, xdr_%s, (char *)%s%s)) {\n",
		proc, transp, arg, prefix, arg);
}