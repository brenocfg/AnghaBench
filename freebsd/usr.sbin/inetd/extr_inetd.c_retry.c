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
struct servtab {int se_fd; struct servtab* se_next; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISMUX (struct servtab*) ; 
 struct servtab* servtab ; 
 int /*<<< orphan*/  setup (struct servtab*) ; 
 scalar_t__ timingout ; 

__attribute__((used)) static void
retry(void)
{
	struct servtab *sep;

	timingout = 0;
	for (sep = servtab; sep; sep = sep->se_next)
		if (sep->se_fd == -1 && !ISMUX(sep))
			setup(sep);
}