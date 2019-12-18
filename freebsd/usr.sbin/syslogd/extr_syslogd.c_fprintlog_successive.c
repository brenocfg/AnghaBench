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
struct filed {int f_prevcount; } ;
typedef  int /*<<< orphan*/  msg ;

/* Variables and functions */
 int /*<<< orphan*/  LocalHostName ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  fprintlog_first (struct filed*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

__attribute__((used)) static void
fprintlog_successive(struct filed *f, int flags)
{
	char msg[100];

	assert(f->f_prevcount > 0);
	snprintf(msg, sizeof(msg), "last message repeated %d times",
	    f->f_prevcount);
	fprintlog_first(f, LocalHostName, "syslogd", NULL, NULL, NULL, msg,
	    flags);
}