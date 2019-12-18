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
struct TYPE_3__ {int value; int /*<<< orphan*/  str; } ;

/* Variables and functions */
 TYPE_1__* elftypes ; 
 size_t nitems (TYPE_1__*) ; 
 scalar_t__ strcasecmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
elftype(const char *elfstrtype)
{
	size_t elfwalk;

	for (elfwalk = 0; elfwalk < nitems(elftypes); elfwalk++)
		if (strcasecmp(elfstrtype, elftypes[elfwalk].str) == 0)
			return (elftypes[elfwalk].value);
	return (-1);
}