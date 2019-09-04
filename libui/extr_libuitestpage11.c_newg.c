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
typedef  int /*<<< orphan*/  uiGroup ;

/* Variables and functions */
 int /*<<< orphan*/  uiGroupSetChild (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * uiNewGroup (char const*) ; 

__attribute__((used)) static uiGroup *newg(const char *n, int s)
{
	uiGroup *g;

	g = uiNewGroup(n);
	if (s)
		uiGroupSetChild(g, NULL);
	return g;
}