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
typedef  int /*<<< orphan*/  pcap_t ;

/* Variables and functions */
 int enter_rfmon_mode_mac80211 (int /*<<< orphan*/ *,int,char const*) ; 
 int enter_rfmon_mode_wext (int /*<<< orphan*/ *,int,char const*) ; 

__attribute__((used)) static int
enter_rfmon_mode(pcap_t *handle, int sock_fd, const char *device)
{
#if defined(HAVE_LIBNL) || defined(IW_MODE_MONITOR)
	int ret;
#endif

#ifdef HAVE_LIBNL
	ret = enter_rfmon_mode_mac80211(handle, sock_fd, device);
	if (ret < 0)
		return ret;	/* error attempting to do so */
	if (ret == 1)
		return 1;	/* success */
#endif /* HAVE_LIBNL */

#ifdef IW_MODE_MONITOR
	ret = enter_rfmon_mode_wext(handle, sock_fd, device);
	if (ret < 0)
		return ret;	/* error attempting to do so */
	if (ret == 1)
		return 1;	/* success */
#endif /* IW_MODE_MONITOR */

	/*
	 * Either none of the mechanisms we know about work or none
	 * of those mechanisms are available, so we can't do monitor
	 * mode.
	 */
	return 0;
}