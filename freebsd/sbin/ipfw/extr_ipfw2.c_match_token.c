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
typedef  scalar_t__ uint ;
struct _s_x {char const* s; int x; } ;

/* Variables and functions */
 int /*<<< orphan*/  bcmp (char const*,char const*,scalar_t__) ; 
 scalar_t__ strlen (char const*) ; 

int
match_token(struct _s_x *table, const char *string)
{
	struct _s_x *pt;
	uint i = strlen(string);

	for (pt = table ; i && pt->s != NULL ; pt++)
		if (strlen(pt->s) == i && !bcmp(string, pt->s, i))
			return pt->x;
	return (-1);
}