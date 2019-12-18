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
 scalar_t__ PJDLOG_INITIALIZED ; 
 int /*<<< orphan*/  assert (int) ; 
 int pjdlog_debug_level ; 
 scalar_t__ pjdlog_initialized ; 

void
pjdlog_debug_set(int level)
{

	assert(pjdlog_initialized == PJDLOG_INITIALIZED);
	assert(level >= 0);
	assert(level <= 127);

	pjdlog_debug_level = level;
}