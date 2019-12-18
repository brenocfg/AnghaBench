#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  explain; int /*<<< orphan*/  ents; int /*<<< orphan*/  number; int /*<<< orphan*/  cputype; } ;

/* Variables and functions */
 int /*<<< orphan*/  BROADWELL_COUNT ; 
 int /*<<< orphan*/  broadwell ; 
 int /*<<< orphan*/  explain_name_broad ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 TYPE_1__ the_cpu ; 

__attribute__((used)) static void
set_broadwell(void)
{
	strcpy(the_cpu.cputype, "HASWELL PMC");
	the_cpu.number = BROADWELL_COUNT;
	the_cpu.ents = broadwell;
	the_cpu.explain = explain_name_broad;
}