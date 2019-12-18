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
typedef  int /*<<< orphan*/  uintmax_t ;
struct timeval {scalar_t__ tv_usec; scalar_t__ tv_sec; } ;
struct filemon {int /*<<< orphan*/  lock; struct file* fp; int /*<<< orphan*/  msgbufr; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SA_XLOCKED ; 
 int /*<<< orphan*/  curthread ; 
 int /*<<< orphan*/  fdrop (struct file*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  filemon_output (struct filemon*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  getmicrotime (struct timeval*) ; 
 size_t snprintf (int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sx_xlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xunlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
filemon_close_log(struct filemon *filemon)
{
	struct file *fp;
	struct timeval now;
	size_t len;

	sx_assert(&filemon->lock, SA_XLOCKED);
	if (filemon->fp == NULL)
		return;

	getmicrotime(&now);

	len = snprintf(filemon->msgbufr,
	    sizeof(filemon->msgbufr),
	    "# Stop %ju.%06ju\n# Bye bye\n",
	    (uintmax_t)now.tv_sec, (uintmax_t)now.tv_usec);

	if (len < sizeof(filemon->msgbufr))
		filemon_output(filemon, filemon->msgbufr, len);
	fp = filemon->fp;
	filemon->fp = NULL;

	sx_xunlock(&filemon->lock);
	fdrop(fp, curthread);
	sx_xlock(&filemon->lock);
}