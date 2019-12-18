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
 scalar_t__ fclose (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  infile ; 
 int /*<<< orphan*/  outfile ; 
 int /*<<< orphan*/  outfp ; 
 scalar_t__ strlen (char const*) ; 
 scalar_t__ strncmp (char const*,char const*,size_t) ; 
 scalar_t__ strspn (char const*,char*) ; 
 int /*<<< orphan*/  warn (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warnx (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static int
checkend(const char *ptr, const char *end, const char *msg)
{
	size_t n;

	n = strlen(end);
	if (strncmp(ptr, end, n) != 0 ||
	    strspn(ptr + n, " \t\r\n") != strlen(ptr + n)) {
		warnx("%s: %s: %s", infile, outfile, msg);
		return (1);
	}
	if (fclose(outfp) != 0) {
		warn("%s: %s", infile, outfile);
		return (1);
	}
	return (0);
}