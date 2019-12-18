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
typedef  int /*<<< orphan*/  u_char ;
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct sockaddr_dl {int sdl_family; scalar_t__ sdl_nlen; int /*<<< orphan*/  sdl_alen; int /*<<< orphan*/  sdl_data; } ;
struct if_msghdr {scalar_t__ ifm_type; int ifm_addrs; int /*<<< orphan*/  ifm_msglen; } ;
typedef  int /*<<< orphan*/  dlpi_handle_t ;

/* Variables and functions */
 int AF_LINK ; 
 int AF_ROUTE ; 
 int CTL_NET ; 
 int DLPI_PHYSADDR_MAX ; 
 int DLPI_SUCCESS ; 
 int /*<<< orphan*/  DL_CURR_PHYS_ADDR ; 
 int /*<<< orphan*/  ESRCH ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/ * LLADDR (struct sockaddr_dl*) ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 int NET_RT_IFLIST ; 
 int RTA_IFP ; 
 scalar_t__ RTM_IFINFO ; 
 int /*<<< orphan*/  dlpi_close (int /*<<< orphan*/ ) ; 
 int dlpi_get_physaddr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 int dlpi_open (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dlpi_strerror (int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  os_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * os_malloc (size_t) ; 
 scalar_t__ os_memcmp (int /*<<< orphan*/ ,char const*,scalar_t__) ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ sysctl (int*,int,int /*<<< orphan*/ *,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int eth_get(const char *device, u8 ea[ETH_ALEN])
{
#ifdef __sun__
	dlpi_handle_t dh;
	u32 physaddrlen = DLPI_PHYSADDR_MAX;
	u8 physaddr[DLPI_PHYSADDR_MAX];
	int retval;

	retval = dlpi_open(device, &dh, 0);
	if (retval != DLPI_SUCCESS) {
		wpa_printf(MSG_ERROR, "dlpi_open error: %s",
			   dlpi_strerror(retval));
		return -1;
	}

	retval = dlpi_get_physaddr(dh, DL_CURR_PHYS_ADDR, physaddr,
				   &physaddrlen);
	if (retval != DLPI_SUCCESS) {
		wpa_printf(MSG_ERROR, "dlpi_get_physaddr error: %s",
			   dlpi_strerror(retval));
		dlpi_close(dh);
		return -1;
	}
	os_memcpy(ea, physaddr, ETH_ALEN);
	dlpi_close(dh);
#else /* __sun__ */
	struct if_msghdr *ifm;
	struct sockaddr_dl *sdl;
	u_char *p, *buf;
	size_t len;
	int mib[] = { CTL_NET, AF_ROUTE, 0, AF_LINK, NET_RT_IFLIST, 0 };

	if (sysctl(mib, 6, NULL, &len, NULL, 0) < 0)
		return -1;
	if ((buf = os_malloc(len)) == NULL)
		return -1;
	if (sysctl(mib, 6, buf, &len, NULL, 0) < 0) {
		os_free(buf);
		return -1;
	}
	for (p = buf; p < buf + len; p += ifm->ifm_msglen) {
		ifm = (struct if_msghdr *)p;
		sdl = (struct sockaddr_dl *)(ifm + 1);
		if (ifm->ifm_type != RTM_IFINFO ||
		    (ifm->ifm_addrs & RTA_IFP) == 0)
			continue;
		if (sdl->sdl_family != AF_LINK || sdl->sdl_nlen == 0 ||
		    os_memcmp(sdl->sdl_data, device, sdl->sdl_nlen) != 0)
			continue;
		os_memcpy(ea, LLADDR(sdl), sdl->sdl_alen);
		break;
	}
	os_free(buf);

	if (p >= buf + len) {
		errno = ESRCH;
		return -1;
	}
#endif /* __sun__ */
	return 0;
}