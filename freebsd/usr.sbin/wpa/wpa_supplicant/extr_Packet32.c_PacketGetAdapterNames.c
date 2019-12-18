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
struct sockaddr_dl {int sdl_nlen; int /*<<< orphan*/  sdl_data; } ;
struct if_msghdr {scalar_t__ ifm_type; int /*<<< orphan*/  ifm_msglen; } ;
typedef  int ULONG ;
typedef  char CHAR ;

/* Variables and functions */
 int CTL_NET ; 
 int FALSE ; 
 int NET_RT_IFLIST ; 
 int PF_ROUTE ; 
 scalar_t__ RTM_IFINFO ; 
 int TRUE ; 
 int /*<<< orphan*/  bzero (char*,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (size_t) ; 
 int /*<<< orphan*/  strncpy (char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ strnstr (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ sysctl (int*,int,char*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
PacketGetAdapterNames(CHAR *namelist, ULONG *len)
{
	int			mib[6];
	size_t			needed;
	struct if_msghdr	*ifm;
	struct sockaddr_dl	*sdl;
	char			*buf, *lim, *next;
	char			*plist;
	int			spc;
	int			i, ifcnt = 0;

	plist = namelist;
	spc = 0;

	bzero(plist, *len);

	needed = 0;
	mib[0] = CTL_NET;
	mib[1] = PF_ROUTE;
	mib[2] = 0;             /* protocol */
	mib[3] = 0;             /* wildcard address family */
	mib[4] = NET_RT_IFLIST;
	mib[5] = 0;             /* no flags */

	if (sysctl (mib, 6, NULL, &needed, NULL, 0) < 0)
		return(FALSE);

	buf = malloc (needed);
	if (buf == NULL)
		return(FALSE);

	if (sysctl (mib, 6, buf, &needed, NULL, 0) < 0) {
		free(buf);
		return(FALSE);
	}

	lim = buf + needed;

	/* Generate interface name list. */

	next = buf;
	while (next < lim) {
		ifm = (struct if_msghdr *)next;
		if (ifm->ifm_type == RTM_IFINFO) {
			sdl = (struct sockaddr_dl *)(ifm + 1);
			if (strnstr(sdl->sdl_data, "wlan", sdl->sdl_nlen)) {
				if ((spc + sdl->sdl_nlen) > *len) {
					free(buf);
					return(FALSE);
				}
				strncpy(plist, sdl->sdl_data, sdl->sdl_nlen);
				plist += (sdl->sdl_nlen + 1);
				spc += (sdl->sdl_nlen + 1);
				ifcnt++;
			}
		}
		next += ifm->ifm_msglen;
	}


	/* Insert an extra "" as a spacer */

	plist++;
	spc++;

	/*
	 * Now generate the interface description list. There
	 * must be a unique description for each interface, and
	 * they have to match what the ndis_events program will
	 * feed in later. To keep this simple, we just repeat
	 * the interface list over again.
	 */

	next = buf;
	while (next < lim) {
		ifm = (struct if_msghdr *)next;
		if (ifm->ifm_type == RTM_IFINFO) {
			sdl = (struct sockaddr_dl *)(ifm + 1);
			if (strnstr(sdl->sdl_data, "wlan", sdl->sdl_nlen)) {
				if ((spc + sdl->sdl_nlen) > *len) {
					free(buf);
					return(FALSE);
				}
				strncpy(plist, sdl->sdl_data, sdl->sdl_nlen);
				plist += (sdl->sdl_nlen + 1);
				spc += (sdl->sdl_nlen + 1);
				ifcnt++;
			}
		}
		next += ifm->ifm_msglen;
	}

	free (buf);

	*len = spc + 1;

	return(TRUE);
}