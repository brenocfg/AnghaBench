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
typedef  int /*<<< orphan*/  uid_t ;

/* Variables and functions */
 int /*<<< orphan*/  err (int,char*,char const*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  errx (int,char*,char const*,char const*) ; 
 int /*<<< orphan*/  strtoul (char const*,char**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static uid_t
num_id(const char *name, const char *type)
{
	uid_t val;
	char *ep;

	errno = 0;
	val = strtoul(name, &ep, 0);
	if (errno) {
		err(1, "%s", name);
	}
	if (*ep != '\0') {
		errx(1, "%s: illegal %s name", name, type);
	}
	return (val);
}