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
 int col ; 
 int /*<<< orphan*/  flushln () ; 
 int maxcol ; 

__attribute__((used)) static void
fwd(void)
{
	int oldcol, oldmax;

	oldcol = col;
	oldmax = maxcol;
	flushln();
	col = oldcol;
	maxcol = oldmax;
}