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
struct iodesc {char* myea; } ;
typedef  int /*<<< orphan*/  phandle_t ;

/* Variables and functions */
 scalar_t__ OF_call_method (char*,int,int,int,int,char**) ; 
 int /*<<< orphan*/  OF_enter () ; 
 int /*<<< orphan*/  OF_finddevice (char*) ; 
 int OF_getprop (int /*<<< orphan*/ ,char*,char*,int) ; 
 int OF_open (char*) ; 
 int /*<<< orphan*/  chosen ; 
 char* dmabuf ; 
 char* ether_sprintf (char*) ; 
 int netinstance ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 char* strchr (char*,char) ; 

__attribute__((used)) static void
ofwn_init(struct iodesc *desc, void *machdep_hint)
{
	phandle_t	netdev;
	char		path[64];
	char		*ch;
	int		pathlen;

	pathlen = OF_getprop(chosen, "bootpath", path, 64);
	if ((ch = strchr(path, ':')) != NULL)
		*ch = '\0';
	netdev = OF_finddevice(path);
#ifdef __sparc64__
	if (OF_getprop(netdev, "mac-address", desc->myea, 6) == -1)
#else
	if (OF_getprop(netdev, "local-mac-address", desc->myea, 6) == -1)
#endif
		goto punt;

	printf("boot: ethernet address: %s\n", ether_sprintf(desc->myea));

	if ((netinstance = OF_open(path)) == -1) {
		printf("Could not open network device.\n");
		goto punt;
	}

#if defined(NETIF_DEBUG)
	printf("ofwn_init: Open Firmware instance handle: %08x\n", netinstance);
#endif

#ifndef __sparc64__
	dmabuf = NULL;
	if (OF_call_method("dma-alloc", netinstance, 1, 1, (64 * 1024), &dmabuf)
	    < 0) {   
		printf("Failed to allocate DMA buffer (got %p).\n", dmabuf);
		goto punt;
	}

#if defined(NETIF_DEBUG)
	printf("ofwn_init: allocated DMA buffer: %p\n", dmabuf);
#endif
#endif

	return;

punt:
	printf("\n");
	printf("Could not boot from %s.\n", path);
	OF_enter();
}