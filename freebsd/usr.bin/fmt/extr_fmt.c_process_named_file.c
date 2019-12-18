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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  n_errors ; 
 int /*<<< orphan*/  process_stream (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  warn (char*,char const*) ; 

__attribute__((used)) static void
process_named_file(const char *name)
{
	FILE *f = fopen(name, "r");

	if (!f) {
		warn("%s", name);
		++n_errors;
	} else {
		process_stream(f, name);
		if (ferror(f)) {
			warn("%s", name);
			++n_errors;
		}
		fclose(f);
	}
}