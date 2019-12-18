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
struct position {int /*<<< orphan*/  line; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  CURRENT_LINE ; 
 int /*<<< orphan*/  CURRENT_NAME ; 
 int MAXRECORD ; 

__attribute__((used)) static void
record(struct position *t, int lev)
{
	if (lev < MAXRECORD) {
		t[lev].name = CURRENT_NAME;
		t[lev].line = CURRENT_LINE;
	}
}