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
struct TYPE_2__ {scalar_t__ s_cond; int /*<<< orphan*/  s_file; scalar_t__ s_loading; } ;

/* Variables and functions */
 scalar_t__ CANY ; 
 int /*<<< orphan*/  Fclose (int /*<<< orphan*/ ) ; 
 scalar_t__ cond ; 
 int /*<<< orphan*/  input ; 
 scalar_t__ loading ; 
 int /*<<< orphan*/  printf (char*) ; 
 scalar_t__ sourcing ; 
 size_t ssp ; 
 TYPE_1__* sstack ; 

int
unstack(void)
{
	if (ssp <= 0) {
		printf("\"Source\" stack over-pop.\n");
		sourcing = 0;
		return (1);
	}
	(void)Fclose(input);
	if (cond != CANY)
		printf("Unmatched \"if\"\n");
	ssp--;
	cond = sstack[ssp].s_cond;
	loading = sstack[ssp].s_loading;
	input = sstack[ssp].s_file;
	if (ssp == 0)
		sourcing = loading;
	return (0);
}