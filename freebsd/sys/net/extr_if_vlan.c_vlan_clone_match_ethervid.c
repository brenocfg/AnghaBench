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
struct ifnet {int dummy; } ;

/* Variables and functions */
 int IFNAMSIZ ; 
 int /*<<< orphan*/  if_rele (struct ifnet*) ; 
 struct ifnet* ifunit_ref (char*) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,int) ; 

__attribute__((used)) static struct ifnet *
vlan_clone_match_ethervid(const char *name, int *vidp)
{
	char ifname[IFNAMSIZ];
	char *cp;
	struct ifnet *ifp;
	int vid;

	strlcpy(ifname, name, IFNAMSIZ);
	if ((cp = strchr(ifname, '.')) == NULL)
		return (NULL);
	*cp = '\0';
	if ((ifp = ifunit_ref(ifname)) == NULL)
		return (NULL);
	/* Parse VID. */
	if (*++cp == '\0') {
		if_rele(ifp);
		return (NULL);
	}
	vid = 0;
	for(; *cp >= '0' && *cp <= '9'; cp++)
		vid = (vid * 10) + (*cp - '0');
	if (*cp != '\0') {
		if_rele(ifp);
		return (NULL);
	}
	if (vidp != NULL)
		*vidp = vid;

	return (ifp);
}