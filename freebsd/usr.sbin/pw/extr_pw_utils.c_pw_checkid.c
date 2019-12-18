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
typedef  int /*<<< orphan*/  uintmax_t ;

/* Variables and functions */
 int /*<<< orphan*/  EX_USAGE ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*,char*,char const*) ; 
 int /*<<< orphan*/  strtounum (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const**) ; 

uintmax_t
pw_checkid(char *nptr, uintmax_t maxval)
{
	const char *errstr = NULL;
	uintmax_t id;

	id = strtounum(nptr, 0, maxval, &errstr);
	if (errstr)
		errx(EX_USAGE, "Bad id '%s': %s", nptr, errstr);
	return (id);
}