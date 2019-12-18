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
struct msghdr {int msg_iovlen; struct iovec* msg_iov; } ;
struct ip {scalar_t__ ip_p; int ip_hl; unsigned short ip_id; } ;
struct iovec {char* iov_base; int iov_len; } ;
typedef  int /*<<< orphan*/  mh ;
typedef  int /*<<< orphan*/  iov ;

/* Variables and functions */
 int /*<<< orphan*/  hexdump (char*,int) ; 
 unsigned short htons (int) ; 
 int /*<<< orphan*/  memcpy (char*,unsigned short*,int) ; 
 int /*<<< orphan*/  memset (struct msghdr*,int /*<<< orphan*/ ,int) ; 
 int ntohs (unsigned short) ; 
 int /*<<< orphan*/  printf (char*,int,int) ; 
 int sendmsg (int,struct msghdr*,int /*<<< orphan*/ ) ; 

int handle_data(int dude, char *buf, int len)
{
	struct ip *ih;
	unsigned short id;
	char tmp[4];
	struct iovec iov[2];
	struct msghdr mh;

	ih = (struct ip*) buf;

	/* XXX IP FRAGS */

	/* filter */
	if (ih->ip_p != 0)
		return 0;

	if (ih->ip_hl != 5)
		return 0;

	/* get info */
	id = ih->ip_id;
	len -= 20;
	buf += 20;
	printf("Got %d bytes [%d]\n", len, ntohs(id));
#if 0	
	hexdump(buf, len);
#endif

	/* prepare packet */
	memcpy(tmp, &id, 2);
	id = htons(len);
	memcpy(&tmp[2], &id, 2);

	iov[0].iov_base = tmp;
	iov[0].iov_len = 4;
	iov[1].iov_base = buf;
	iov[1].iov_len = len;

	memset(&mh, 0, sizeof(mh));
	mh.msg_iov = iov;
	mh.msg_iovlen = sizeof(iov)/sizeof(struct iovec);

	/* write */
	if (sendmsg(dude, &mh, 0) != (4 + len))
		return -1;
	return 0;
}