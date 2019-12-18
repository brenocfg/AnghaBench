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

/* Variables and functions */
 int /*<<< orphan*/  fivesome_drop_work (char*,int,int) ; 

__attribute__((used)) static void
fivesome_drop(void)
{

	fivesome_drop_work("fivesome_drop1", 0, 0);
	fivesome_drop_work("fivesome_drop2", 0, 1);
	fivesome_drop_work("fivesome_drop3", 1, 0);
	fivesome_drop_work("fivesome_drop4", 1, 1);
}