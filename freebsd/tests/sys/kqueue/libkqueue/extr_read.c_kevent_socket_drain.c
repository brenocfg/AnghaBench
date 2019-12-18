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
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  puts (char*) ; 
 int read (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/ * sockfd ; 

__attribute__((used)) static void
kevent_socket_drain(void)
{
    char buf[1];

    /* Drain the read buffer, then make sure there are no more events. */
    puts("draining the read buffer");
    if (read(sockfd[0], &buf[0], 1) < 1)
        err(1, "read(2)");
}