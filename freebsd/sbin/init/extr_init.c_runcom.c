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
typedef  int /*<<< orphan*/ * state_func_t ;

/* Variables and functions */
 int /*<<< orphan*/  AUTOBOOT ; 
 int /*<<< orphan*/  _PATH_RUNCOM ; 
 int /*<<< orphan*/  read_ttys ; 
 int /*<<< orphan*/ * run_script (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  runcom_mode ; 

__attribute__((used)) static state_func_t
runcom(void)
{
	state_func_t next_transition;

	if ((next_transition = run_script(_PATH_RUNCOM)) != NULL)
		return next_transition;

	runcom_mode = AUTOBOOT;		/* the default */
	return (state_func_t) read_ttys;
}