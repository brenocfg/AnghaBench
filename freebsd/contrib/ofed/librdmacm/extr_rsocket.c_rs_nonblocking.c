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
struct rsocket {int fd_flags; } ;

/* Variables and functions */
 int MSG_DONTWAIT ; 
 int O_NONBLOCK ; 

__attribute__((used)) static int rs_nonblocking(struct rsocket *rs, int flags)
{
	return (rs->fd_flags & O_NONBLOCK) || (flags & MSG_DONTWAIT);
}