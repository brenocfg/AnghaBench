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
struct stat {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  crash () ; 
 scalar_t__ stat (char const*,struct stat*) ; 
 int /*<<< orphan*/  warn (char*,char const*) ; 
 int /*<<< orphan*/  warnx (char*,char const*) ; 

__attribute__((used)) static void
checkfiles(const char *infile, const char *outfile)
{

	struct stat buf;

	if (infile)		/* infile ! = NULL */
		if (stat(infile, &buf) < 0)
		{
			warn("%s", infile);
			crash();
		}
	if (outfile) {
		if (stat(outfile, &buf) < 0)
			return;	/* file does not exist */
		else {
			warnx("file '%s' already exists and may be overwritten", outfile);
			crash();
		}
	}
}