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
struct option {char* value; char* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  FREEPTR (char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,...) ; 
 char* ftp_strdup (char const*) ; 
 struct option* getoption (char const*) ; 
 int /*<<< orphan*/  ttyout ; 
 scalar_t__ verbose ; 

void
set_option(const char * option, const char * value, int doverbose)
{
	struct option *o;

	o = getoption(option);
	if (o == NULL) {
		fprintf(ttyout, "No such option `%s'.\n", option);
		return;
	}
	FREEPTR(o->value);
	o->value = ftp_strdup(value);
	if (verbose && doverbose)
		fprintf(ttyout, "Setting `%s' to `%s'.\n",
		    o->name, o->value);
}