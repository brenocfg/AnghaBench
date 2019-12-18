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
typedef  int /*<<< orphan*/  va_list ;

/* Variables and functions */
 scalar_t__ PJDLOG_INITIALIZED ; 
 int PJDLOG_PREFIX_STACK ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ pjdlog_initialized ; 
 int pjdlog_prefix_current ; 
 int /*<<< orphan*/  pjdlogv_prefix_set (char const*,int /*<<< orphan*/ ) ; 

void
pjdlogv_prefix_push(const char *fmt, va_list ap)
{

	assert(pjdlog_initialized == PJDLOG_INITIALIZED);
	assert(pjdlog_prefix_current < PJDLOG_PREFIX_STACK - 1);

	pjdlog_prefix_current++;

	pjdlogv_prefix_set(fmt, ap);
}