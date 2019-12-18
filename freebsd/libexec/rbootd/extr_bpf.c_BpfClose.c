#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/ * sa_data; int /*<<< orphan*/  sa_family; scalar_t__ sa_len; } ;
struct ifreq {TYPE_1__ ifr_addr; } ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  AF_UNSPEC ; 
 int /*<<< orphan*/  BIOCPROMISC ; 
 int BpfFd ; 
 int /*<<< orphan*/ * BpfPkt ; 
 scalar_t__ RMP_ADDRLEN ; 
 int /*<<< orphan*/ * RmpMcastAddr ; 
 int /*<<< orphan*/  SIOCDELMULTI ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memmove (char*,int /*<<< orphan*/ *,scalar_t__) ; 

void
BpfClose(void)
{
	struct ifreq ifr;

	if (BpfPkt != NULL) {
		free((char *)BpfPkt);
		BpfPkt = NULL;
	}

	if (BpfFd == -1)
		return;

#ifdef MSG_EOR
	ifr.ifr_addr.sa_len = RMP_ADDRLEN + 2;
#endif
	ifr.ifr_addr.sa_family = AF_UNSPEC;
	memmove((char *)&ifr.ifr_addr.sa_data[0], &RmpMcastAddr[0], RMP_ADDRLEN);
	if (ioctl(BpfFd, SIOCDELMULTI, (caddr_t)&ifr) < 0)
		(void) ioctl(BpfFd, BIOCPROMISC, (caddr_t)0);

	(void) close(BpfFd);
	BpfFd = -1;
}