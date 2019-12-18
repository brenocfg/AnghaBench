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
typedef  int /*<<< orphan*/  module_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  EVENTHANDLER_DEREGISTER (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVENTHANDLER_PRI_ANY ; 
 int /*<<< orphan*/  EVENTHANDLER_REGISTER (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
#define  MOD_LOAD 129 
#define  MOD_UNLOAD 128 
 int /*<<< orphan*/  bootverbose ; 
 int /*<<< orphan*/  bpf_track ; 
 int /*<<< orphan*/  if_clone_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_clone_simple (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iflladdr_event ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  wlan_bpfevent ; 
 int /*<<< orphan*/  wlan_clone_create ; 
 int /*<<< orphan*/  wlan_clone_destroy ; 
 int /*<<< orphan*/  wlan_cloner ; 
 int /*<<< orphan*/  wlan_iflladdr ; 
 int /*<<< orphan*/  wlan_ifllevent ; 
 int /*<<< orphan*/  wlanname ; 

__attribute__((used)) static int
wlan_modevent(module_t mod, int type, void *unused)
{
	switch (type) {
	case MOD_LOAD:
		if (bootverbose)
			printf("wlan: <802.11 Link Layer>\n");
		wlan_bpfevent = EVENTHANDLER_REGISTER(bpf_track,
		    bpf_track, 0, EVENTHANDLER_PRI_ANY);
		wlan_ifllevent = EVENTHANDLER_REGISTER(iflladdr_event,
		    wlan_iflladdr, NULL, EVENTHANDLER_PRI_ANY);
		wlan_cloner = if_clone_simple(wlanname, wlan_clone_create,
		    wlan_clone_destroy, 0);
		return 0;
	case MOD_UNLOAD:
		if_clone_detach(wlan_cloner);
		EVENTHANDLER_DEREGISTER(bpf_track, wlan_bpfevent);
		EVENTHANDLER_DEREGISTER(iflladdr_event, wlan_ifllevent);
		return 0;
	}
	return EINVAL;
}