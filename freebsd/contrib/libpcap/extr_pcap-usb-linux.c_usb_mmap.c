#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pcap_usb_linux {int mmapbuflen; scalar_t__ mmapbuf; } ;
struct TYPE_3__ {int /*<<< orphan*/  fd; struct pcap_usb_linux* priv; } ;
typedef  TYPE_1__ pcap_t ;

/* Variables and functions */
 scalar_t__ MAP_FAILED ; 
 int /*<<< orphan*/  MAP_SHARED ; 
 int /*<<< orphan*/  MON_IOCQ_RING_SIZE ; 
 int /*<<< orphan*/  PROT_READ ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ mmap (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
int usb_mmap(pcap_t* handle)
{
	struct pcap_usb_linux *handlep = handle->priv;
	int len = ioctl(handle->fd, MON_IOCQ_RING_SIZE);
	if (len < 0)
		return 0;

	handlep->mmapbuflen = len;
	handlep->mmapbuf = mmap(0, handlep->mmapbuflen, PROT_READ,
	    MAP_SHARED, handle->fd, 0);
	return handlep->mmapbuf != MAP_FAILED;
}