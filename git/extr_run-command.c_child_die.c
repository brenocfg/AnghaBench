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
struct child_err {int err; int /*<<< orphan*/  syserr; } ;
typedef  enum child_errcode { ____Placeholder_child_errcode } child_errcode ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  _exit (int) ; 
 int /*<<< orphan*/  child_notifier ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  xwrite (int /*<<< orphan*/ ,struct child_err*,int) ; 

__attribute__((used)) static void child_die(enum child_errcode err)
{
	struct child_err buf;

	buf.err = err;
	buf.syserr = errno;

	/* write(2) on buf smaller than PIPE_BUF (min 512) is atomic: */
	xwrite(child_notifier, &buf, sizeof(buf));
	_exit(1);
}