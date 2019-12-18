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
 int /*<<< orphan*/ * sockfd ; 
 int write (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void
kevent_socket_fill(void)
{
  puts("filling the read buffer");
    if (write(sockfd[1], ".", 1) < 1)
        err(1, "write(2)");
}