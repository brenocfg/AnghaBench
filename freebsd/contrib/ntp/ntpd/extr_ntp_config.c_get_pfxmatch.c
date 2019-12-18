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
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ *) ; 
 scalar_t__ strncmp (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u_int32
get_pfxmatch(
	const char **	pstr,
	struct masks *	m
	)
{
	while (m->name != NULL) {
		if (strncmp(*pstr, m->name, strlen(m->name)) == 0) {
			*pstr += strlen(m->name);
			return m->mask;
		} else {
			m++;
		}
	}
	return 0;
}