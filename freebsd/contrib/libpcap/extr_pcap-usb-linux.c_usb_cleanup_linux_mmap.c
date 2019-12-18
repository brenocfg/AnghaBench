#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct pcap_usb_linux {int /*<<< orphan*/ * mmapbuf; int /*<<< orphan*/  mmapbuflen; } ;
struct TYPE_4__ {struct pcap_usb_linux* priv; } ;
typedef  TYPE_1__ pcap_t ;

/* Variables and functions */
 int /*<<< orphan*/  munmap (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcap_cleanup_live_common (TYPE_1__*) ; 

__attribute__((used)) static void
usb_cleanup_linux_mmap(pcap_t* handle)
{
	struct pcap_usb_linux *handlep = handle->priv;

	/* if we have a memory-mapped buffer, unmap it */
	if (handlep->mmapbuf != NULL) {
		munmap(handlep->mmapbuf, handlep->mmapbuflen);
		handlep->mmapbuf = NULL;
	}
	pcap_cleanup_live_common(handle);
}