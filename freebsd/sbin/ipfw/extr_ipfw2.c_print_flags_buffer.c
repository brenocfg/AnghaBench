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
typedef  int uint32_t ;
struct _s_x {int x; int /*<<< orphan*/  s; } ;

/* Variables and functions */
 int snprintf (char*,size_t,char*,char const*,int /*<<< orphan*/ ) ; 

void
print_flags_buffer(char *buf, size_t sz, struct _s_x *list, uint32_t set)
{
	char const *comma = "";
	int i, l;

	for (i = 0; list[i].x != 0; i++) {
		if ((set & list[i].x) == 0)
			continue;
		
		set &= ~list[i].x;
		l = snprintf(buf, sz, "%s%s", comma, list[i].s);
		if (l >= sz)
			return;
		comma = ",";
		buf += l;
		sz -=l;
	}
}