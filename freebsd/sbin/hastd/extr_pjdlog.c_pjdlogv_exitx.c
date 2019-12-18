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
 int /*<<< orphan*/  LOG_ERR ; 
 scalar_t__ PJDLOG_INITIALIZED ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  exit (int) ; 
 scalar_t__ pjdlog_initialized ; 
 int /*<<< orphan*/  pjdlogv (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

void
pjdlogv_exitx(int exitcode, const char *fmt, va_list ap)
{

	assert(pjdlog_initialized == PJDLOG_INITIALIZED);

	pjdlogv(LOG_ERR, fmt, ap);
	exit(exitcode);
	/* NOTREACHED */
}