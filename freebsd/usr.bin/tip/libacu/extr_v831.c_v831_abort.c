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
 int AC ; 
 scalar_t__ FD ; 
 int /*<<< orphan*/  SIGKILL ; 
 int /*<<< orphan*/  TIOCCDTR ; 
 int /*<<< orphan*/  TIOCNXCL ; 
 scalar_t__ child ; 
 int /*<<< orphan*/  close (scalar_t__) ; 
 int /*<<< orphan*/  ioctl (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kill (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/  sleep (int) ; 

void
v831_abort(void)
{
#ifdef DEBUG
        printf("[abort: AC=%d]\n", AC);
#endif
        sleep(2);
        if (child > 0)
                kill(child, SIGKILL);
        if (FD > 0)
                ioctl(FD, TIOCNXCL, NULL);
        close(AC);
        if (FD > 0)
                ioctl(FD, TIOCCDTR, 0);
        close(FD);
}