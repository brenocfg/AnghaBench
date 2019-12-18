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
struct sockaddr_raw {int /*<<< orphan*/  sr_ifname; int /*<<< orphan*/  sr_port; int /*<<< orphan*/  sr_family; } ;
typedef  int /*<<< orphan*/  sr ;

/* Variables and functions */
 int /*<<< orphan*/  AF_RAW ; 
 int /*<<< orphan*/  ETHERTYPE_IP ; 
 int /*<<< orphan*/  PF_RAW ; 
 int /*<<< orphan*/  RAWPROTO_DRAIN ; 
 int /*<<< orphan*/  SOCK_RAW ; 
 scalar_t__ bind (int,struct sockaddr_raw*,int) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  memset (struct sockaddr_raw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,char*,int) ; 

int	initdevice(char *device, int tout)
{
	int fd;
	struct sockaddr_raw sr;

	if ((fd = socket(PF_RAW, SOCK_RAW, RAWPROTO_DRAIN)) < 0)
	    {
		perror("socket(PF_RAW, SOCK_RAW, RAWPROTO_DRAIN)");
		return -1;
	    }

	memset(&sr, 0, sizeof(sr));
	sr.sr_family = AF_RAW;
	sr.sr_port = ETHERTYPE_IP;
	strncpy(sr.sr_ifname, device, sizeof(sr.sr_ifname));
	if (bind(fd, &sr, sizeof(sr)) < 0)
	    {
		perror("bind AF_RAW");
		close(fd);
		return -1;
	    }
	return fd;
}