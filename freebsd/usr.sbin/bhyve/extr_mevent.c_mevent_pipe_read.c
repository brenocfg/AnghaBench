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
typedef  enum ev_type { ____Placeholder_ev_type } ev_type ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int MEVENT_MAX ; 
 int read (int,char*,int) ; 

__attribute__((used)) static void
mevent_pipe_read(int fd, enum ev_type type, void *param)
{
	char buf[MEVENT_MAX];
	int status;

	/*
	 * Drain the pipe read side. The fd is non-blocking so this is
	 * safe to do.
	 */
	do {
		status = read(fd, buf, sizeof(buf));
	} while (status == MEVENT_MAX);
}