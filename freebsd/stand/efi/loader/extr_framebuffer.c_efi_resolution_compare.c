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
struct named_resolution {int /*<<< orphan*/ * alias; int /*<<< orphan*/ * name; } ;

/* Variables and functions */
 scalar_t__ strcasecmp (int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static bool
efi_resolution_compare(struct named_resolution *res, const char *cmp)
{

	if (strcasecmp(res->name, cmp) == 0)
		return (true);
	if (res->alias != NULL && strcasecmp(res->alias, cmp) == 0)
		return (true);
	return (false);
}