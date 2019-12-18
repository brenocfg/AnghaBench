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
 int EINVAL ; 
 int /*<<< orphan*/  LC_CTYPE ; 
 int /*<<< orphan*/ * nls_lower ; 
 int /*<<< orphan*/ * nls_upper ; 
 int /*<<< orphan*/ * setlocale (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  tolower (int) ; 
 int /*<<< orphan*/  toupper (int) ; 
 int /*<<< orphan*/  warnx (char*,char const*) ; 

int
nls_setlocale(const char *name)
{
	int i;

	if (setlocale(LC_CTYPE, name) == NULL) {
		warnx("can't set locale '%s'\n", name);
		return EINVAL;
	}
	for (i = 0; i < 256; i++) {
		nls_lower[i] = tolower(i);
		nls_upper[i] = toupper(i);
	}
	return 0;
}