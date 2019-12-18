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
typedef  scalar_t__ ofwcell_t ;

/* Variables and functions */
 int /*<<< orphan*/  ofw (scalar_t__*) ; 
 int /*<<< orphan*/  stub1 (scalar_t__*) ; 

__attribute__((used)) static void
ofw_exit(void)
{
	ofwcell_t args[3];

	args[0] = (ofwcell_t)"exit";
	args[1] = 0;
	args[2] = 0;

	for (;;)
		(*ofw)(args);
}