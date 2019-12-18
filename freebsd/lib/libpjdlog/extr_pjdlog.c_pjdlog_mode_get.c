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
 scalar_t__ pjdlog_initialized ; 
 int pjdlog_mode ; 

int
pjdlog_mode_get(void)
{

	assert(pjdlog_initialized == PJDLOG_INITIALIZED);

	return (pjdlog_mode);
}