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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  strtoul (char const*,char**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warnx (char*,char const*) ; 

__attribute__((used)) static int
get_int_arg(const char *s, uint32_t *valp)
{
	char *p;

	*valp = strtoul(s, &p, 0);
	if (*p) {
		warnx("bad parameter \"%s\"", s);
		return -1;
	}
	return 0;
}