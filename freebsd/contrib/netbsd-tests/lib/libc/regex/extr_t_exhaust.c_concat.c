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
 int /*<<< orphan*/  ATF_REQUIRE (int /*<<< orphan*/ ) ; 
 char* malloc (size_t) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 size_t strlen (char const*) ; 

__attribute__((used)) static char *
concat(const char *d, const char *s)
{
	size_t dlen = strlen(d);
	size_t slen = strlen(s);
	char *p = malloc(dlen + slen + 1);

	ATF_REQUIRE(p != NULL);
	strcpy(p, d);
	strcpy(p + dlen, s);
	return p;
}