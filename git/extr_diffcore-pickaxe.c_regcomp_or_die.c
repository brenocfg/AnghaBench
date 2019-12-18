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
typedef  int /*<<< orphan*/  regex_t ;

/* Variables and functions */
 int /*<<< orphan*/  die (char*,char*) ; 
 int regcomp (int /*<<< orphan*/ *,char const*,int) ; 
 int /*<<< orphan*/  regerror (int,int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static void regcomp_or_die(regex_t *regex, const char *needle, int cflags)
{
	int err = regcomp(regex, needle, cflags);
	if (err) {
		/* The POSIX.2 people are surely sick */
		char errbuf[1024];
		regerror(err, regex, errbuf, 1024);
		die("invalid regex: %s", errbuf);
	}
}