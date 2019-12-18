#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int ;
struct TYPE_3__ {int /*<<< orphan*/  bit; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 TYPE_1__* flags ; 
 int nitems (TYPE_1__*) ; 
 scalar_t__ strncasecmp (int /*<<< orphan*/ ,char const*,int) ; 

__attribute__((used)) static u_int
getflag(const char *name, int len)
{
	int i;

	for (i = 0; i < nitems(flags); i++)
		if (strncasecmp(flags[i].name, name, len) == 0)
			return flags[i].bit;
	return 0;
}