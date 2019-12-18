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
 scalar_t__ asprintf (char**,char*,char const*,char const*) ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 char* strdup (char*) ; 

__attribute__((used)) static char *
partial_offset(const char *basetype, const char *name, int need_offset)
{
    char *str;
    if (name == NULL || need_offset == 0)
	return strdup("0");
    if (asprintf(&str, "offsetof(struct %s, %s)", basetype, name) < 0 || str == NULL)
	errx(1, "malloc");
    return str;
}