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
 scalar_t__ async_with_fork () ; 
 int /*<<< orphan*/  close (int) ; 
 int recv_sideband (char*,int,int) ; 

__attribute__((used)) static int sideband_demux(int in, int out, void *data)
{
	int *fd = data, ret;
	if (async_with_fork())
		close(fd[1]);
	ret = recv_sideband("send-pack", fd[0], out);
	close(out);
	return ret;
}