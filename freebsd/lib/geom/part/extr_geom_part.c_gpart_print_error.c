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
 int strtol (char const*,char**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warnc (int,char*,...) ; 
 int /*<<< orphan*/  warnx (char*,char*) ; 

__attribute__((used)) static void
gpart_print_error(const char *errstr)
{
	char *errmsg;
	int error;

	error = strtol(errstr, &errmsg, 0);
	if (errmsg != errstr) {
		while (errmsg[0] == ' ')
			errmsg++;
		if (errmsg[0] != '\0')
			warnc(error, "%s", errmsg);
		else
			warnc(error, NULL);
	} else
		warnx("%s", errmsg);
}