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
typedef  int /*<<< orphan*/  uiBox ;

/* Variables and functions */
 int /*<<< orphan*/  append (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  box ; 
 int /*<<< orphan*/ * newvbox () ; 
 int /*<<< orphan*/ * stub1 () ; 

uiBox *newVerticalBox(void)
{
	uiBox *b;

	b = (*newvbox)();
	append(b, box);
	return b;
}