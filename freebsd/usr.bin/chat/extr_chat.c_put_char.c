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
 int /*<<< orphan*/  F_GETFL ; 
 int /*<<< orphan*/  F_SETFL ; 
 int O_NONBLOCK ; 
 int /*<<< orphan*/  STDOUT_FILENO ; 
 int /*<<< orphan*/  chat_logf (char*,int) ; 
 int /*<<< orphan*/  fatal (int,char*) ; 
 int fcntl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usleep (int) ; 
 int write (int /*<<< orphan*/ ,char*,int) ; 

int put_char(int c)
{
    int status;
    char ch = c;

    usleep(10000);		/* inter-character typing delay (?) */

    status = write(STDOUT_FILENO, &ch, 1);

    switch (status) {
    case 1:
	return (0);
	
    default:
	chat_logf("warning: write() on stdout returned %d", status);
	
    case -1:
	if ((status = fcntl(0, F_GETFL, 0)) == -1)
	    fatal(2, "Can't get file mode flags on stdin, %m");

	if (fcntl(0, F_SETFL, status & ~O_NONBLOCK) == -1)
	    fatal(2, "Can't set file mode flags on stdin: %m");
	
	return (-1);
    }
}