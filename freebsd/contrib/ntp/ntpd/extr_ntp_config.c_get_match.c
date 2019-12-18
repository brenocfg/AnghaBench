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
typedef  int /*<<< orphan*/  u_int32 ;
struct masks {int /*<<< orphan*/  mask; int /*<<< orphan*/ * name; } ;

/* Variables and functions */
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static u_int32
get_match(
	const char *	str,
	struct masks *	m
	)
{
	while (m->name != NULL) {
		if (strcmp(str, m->name) == 0)
			return m->mask;
		else
			m++;
	}
	return 0;
}