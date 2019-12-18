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
struct pollfd {int fd; int /*<<< orphan*/  events; } ;

/* Variables and functions */
 int EIO ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  POLLIN ; 
 int poll (struct pollfd*,int,int) ; 

__attribute__((used)) static int dev_poll(int fd, int timeout_ms)
{
	struct pollfd ufds;
	int n;

	ufds.fd = fd;
	ufds.events = POLLIN;

	if ((n = poll(&ufds, 1, timeout_ms)) == 1)
		return 0;

	if (n == 0)
		return -ETIMEDOUT;

	return -EIO;
}