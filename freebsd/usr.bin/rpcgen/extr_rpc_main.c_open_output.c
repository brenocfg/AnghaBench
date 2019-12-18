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
 int /*<<< orphan*/  crash () ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/ * fout ; 
 int /*<<< orphan*/  record_open (char const*) ; 
 int /*<<< orphan*/ * stdout ; 
 scalar_t__ streq (char const*,char const*) ; 
 int /*<<< orphan*/  warn (char*,char const*) ; 
 int /*<<< orphan*/  warnx (char*,char const*) ; 

__attribute__((used)) static void
open_output(const char *infile, const char *outfile)
{

	if (outfile == NULL) {
		fout = stdout;
		return;
	}

	if (infile != NULL && streq(outfile, infile)) {
		warnx("%s already exists. No output generated", infile);
		crash();
	}
	fout = fopen(outfile, "w");
	if (fout == NULL) {
		warn("unable to open %s", outfile);
		crash();
	}
	record_open(outfile);

	return;
}