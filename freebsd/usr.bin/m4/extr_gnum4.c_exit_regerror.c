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
 int /*<<< orphan*/  m4errx (int,char*,char const*,char*) ; 
 size_t regerror (int,int /*<<< orphan*/ *,char*,size_t) ; 
 char* xalloc (size_t,char*,unsigned long) ; 

__attribute__((used)) static void
exit_regerror(int er, regex_t *re, const char *source)
{
	size_t	errlen;
	char	*errbuf;

	errlen = regerror(er, re, NULL, 0);
	errbuf = xalloc(errlen,
	    "malloc in regerror: %lu", (unsigned long)errlen);
	regerror(er, re, errbuf, errlen);
	m4errx(1, "regular expression error in %s: %s.", source, errbuf);
}