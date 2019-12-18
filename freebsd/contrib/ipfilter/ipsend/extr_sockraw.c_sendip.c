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
struct sockaddr_in {int /*<<< orphan*/  sin_addr; int /*<<< orphan*/  sin_family; } ;
struct ether_header {int dummy; } ;
typedef  int /*<<< orphan*/  sin ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  bcopy (char*,char*,int) ; 
 int /*<<< orphan*/  bzero (char*,int) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int sendto (int,char*,int,int /*<<< orphan*/ ,struct sockaddr_in*,int) ; 

int	sendip(int fd, char *pkt, int len)
{
	struct ether_header *eh;
	struct sockaddr_in sin;

	eh = (struct ether_header *)pkt;
	bzero((char *)&sin, sizeof(sin));
	sin.sin_family = AF_INET;
	pkt += 14;
	len -= 14;
	bcopy(pkt + 12, (char *)&sin.sin_addr, 4);

	if (sendto(fd, pkt, len, 0, &sin, sizeof(sin)) == -1)
	    {
		perror("send");
		return -1;
	    }

	return len;
}