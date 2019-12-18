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
struct ssh_channels {int channel_max_fd; } ;
struct ssh {struct ssh_channels* chanctxt; } ;

/* Variables and functions */
 int /*<<< orphan*/  channel_find_maxfd (struct ssh_channels*) ; 
 int close (int) ; 

int
channel_close_fd(struct ssh *ssh, int *fdp)
{
	struct ssh_channels *sc = ssh->chanctxt;
	int ret = 0, fd = *fdp;

	if (fd != -1) {
		ret = close(fd);
		*fdp = -1;
		if (fd == sc->channel_max_fd)
			channel_find_maxfd(sc);
	}
	return ret;
}