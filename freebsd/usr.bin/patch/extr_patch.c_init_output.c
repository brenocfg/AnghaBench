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
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/ * ofp ; 
 int /*<<< orphan*/  pfatal (char*,char const*) ; 

__attribute__((used)) static void
init_output(const char *name)
{
	ofp = fopen(name, "w");
	if (ofp == NULL)
		pfatal("can't create %s", name);
}