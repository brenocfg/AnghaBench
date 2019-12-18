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
 int /*<<< orphan*/  ATF_REQUIRE_MSG (int /*<<< orphan*/ ,char*,size_t,size_t) ; 
 char* malloc (size_t) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 size_t strlen (char const*) ; 

__attribute__((used)) static char *
mkstr(const char *str, size_t len)
{
	size_t slen = strlen(str);
	char *p = malloc(slen * len + 1);
	ATF_REQUIRE_MSG(p != NULL, "slen=%zu, len=%zu", slen, len);
	for (size_t i = 0; i < len; i++)
		strcpy(&p[i * slen], str);
	return p;
}