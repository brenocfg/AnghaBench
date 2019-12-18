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
struct sockaddr {int /*<<< orphan*/  sa_data; int /*<<< orphan*/  sa_family; } ;
struct ifreq {int /*<<< orphan*/  ifr_addr; int /*<<< orphan*/  ifr_name; } ;
typedef  int /*<<< orphan*/  s ;
typedef  int /*<<< orphan*/  ifr ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  IPPROTO_RAW ; 
 int /*<<< orphan*/  SIOCGIFADDR ; 
 int /*<<< orphan*/  SOCK_RAW ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int bind (int,struct sockaddr*,int) ; 
 int /*<<< orphan*/  bzero (char*,int) ; 
 int ioctl (int,int /*<<< orphan*/ ,struct ifreq*) ; 
 int /*<<< orphan*/  memset (struct ifreq*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,char*,int) ; 

int	initdevice(char *device, int tout)
{
	struct sockaddr s;
	struct ifreq ifr;
	int fd;

	memset(&ifr, 0, sizeof(ifr));
	strncpy(ifr.ifr_name, device, sizeof ifr.ifr_name);

	if ((fd = socket(AF_INET, SOCK_RAW, IPPROTO_RAW)) < 0)
	    {
		perror("socket(AF_INET, SOCK_RAW, IPPROTO_RAW)");
		return -1;
	    }

	if (ioctl(fd, SIOCGIFADDR, &ifr) == -1)
	    {
		perror("ioctl SIOCGIFADDR");
		return -1;
	    }

	bzero((char *)&s, sizeof(s));
	s.sa_family = AF_INET;
	bcopy(&ifr.ifr_addr, s.sa_data, 4);
	if (bind(fd, &s, sizeof(s)) == -1)
		perror("bind");
	return fd;
}