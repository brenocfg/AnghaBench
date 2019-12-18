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
struct linkinfo {int /*<<< orphan*/  ourhook; } ;

/* Variables and functions */
 int strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
hook_cmp(const void *p1, const void *p2)
{
	const struct linkinfo *i1 = p1;
	const struct linkinfo *i2 = p2;

	if (strlen(i1->ourhook) < strlen(i2->ourhook))
		return (-1);
	if (strlen(i1->ourhook) > strlen(i2->ourhook))
		return (+1);
	return (strcmp(i1->ourhook, i2->ourhook));
}