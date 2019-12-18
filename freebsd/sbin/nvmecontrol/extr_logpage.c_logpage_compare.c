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
struct logpage_function {scalar_t__ log_page; int /*<<< orphan*/ * vendor; } ;

/* Variables and functions */
 int strcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
logpage_compare(struct logpage_function *a, struct logpage_function *b)
{
	int c;

	if ((a->vendor == NULL) != (b->vendor == NULL))
		return (a->vendor == NULL ? -1 : 1);
	if (a->vendor != NULL) {
		c = strcmp(a->vendor, b->vendor);
		if (c != 0)
			return (c);
	}
	return ((int)a->log_page - (int)b->log_page);
}