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
 scalar_t__ strcasecmp (char const*,char const*) ; 

__attribute__((used)) static int
isinfinite(const char *s)
{
    static const char *infs[] = {
	"infinity",
	"inf",
	"unlimited",
	"unlimit",
	"-1",
	NULL
    };
    const char **i = &infs[0];

    while (*i != NULL) {
	if (strcasecmp(s, *i) == 0)
	    return 1;
	++i;
    }
    return 0;
}