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
 int /*<<< orphan*/  f_print (int /*<<< orphan*/ ,char*,...) ; 
 char const* fixtype (char const*) ; 
 int /*<<< orphan*/  fout ; 
 scalar_t__ streq (char const*,char*) ; 

void
ptype(const char *prefix, const char *type, int follow)
{
	if (prefix != NULL) {
		if (streq(prefix, "enum")) {
			f_print(fout, "enum ");
		} else {
			f_print(fout, "struct ");
		}
	}
	if (streq(type, "bool")) {
		f_print(fout, "bool_t ");
	} else if (streq(type, "string")) {
		f_print(fout, "char *");
	} else {
		f_print(fout, "%s ", follow ? fixtype(type) : type);
	}
}