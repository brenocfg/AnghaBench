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
struct ucred {int dummy; } ;
struct mac {int /*<<< orphan*/  m_string; int /*<<< orphan*/  m_buflen; } ;
struct label {int dummy; } ;
struct ifreq {int dummy; } ;
struct ifnet {int /*<<< orphan*/  if_label; } ;
typedef  int /*<<< orphan*/  mac ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MAC_IFNET_LOCK (struct ifnet*,int) ; 
 int /*<<< orphan*/  MAC_IFNET_UNLOCK (struct ifnet*,int) ; 
 int MPC_OBJECT_IFNET ; 
 int /*<<< orphan*/  M_MACTEMP ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int copyin (int /*<<< orphan*/ ,struct mac*,int) ; 
 int copyinstr (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int copyout (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  free (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ifr_data_get_ptr (struct ifreq*) ; 
 int mac_check_structmac_consistent (struct mac*) ; 
 int /*<<< orphan*/  mac_ifnet_copy_label (int /*<<< orphan*/ ,struct label*) ; 
 int mac_ifnet_externalize_label (struct label*,char*,char*,int /*<<< orphan*/ ) ; 
 struct label* mac_ifnet_label_alloc () ; 
 int /*<<< orphan*/  mac_ifnet_label_free (struct label*) ; 
 int mac_labeled ; 
 char* malloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ strlen (char*) ; 

int
mac_ifnet_ioctl_get(struct ucred *cred, struct ifreq *ifr,
    struct ifnet *ifp)
{
	char *elements, *buffer;
	struct label *intlabel;
	struct mac mac;
	int error, locked;

	if (!(mac_labeled & MPC_OBJECT_IFNET))
		return (EINVAL);

	error = copyin(ifr_data_get_ptr(ifr), &mac, sizeof(mac));
	if (error)
		return (error);

	error = mac_check_structmac_consistent(&mac);
	if (error)
		return (error);

	elements = malloc(mac.m_buflen, M_MACTEMP, M_WAITOK);
	error = copyinstr(mac.m_string, elements, mac.m_buflen, NULL);
	if (error) {
		free(elements, M_MACTEMP);
		return (error);
	}

	buffer = malloc(mac.m_buflen, M_MACTEMP, M_WAITOK | M_ZERO);
	intlabel = mac_ifnet_label_alloc();
	MAC_IFNET_LOCK(ifp, locked);
	mac_ifnet_copy_label(ifp->if_label, intlabel);
	MAC_IFNET_UNLOCK(ifp, locked);
	error = mac_ifnet_externalize_label(intlabel, elements, buffer,
	    mac.m_buflen);
	mac_ifnet_label_free(intlabel);
	if (error == 0)
		error = copyout(buffer, mac.m_string, strlen(buffer)+1);

	free(buffer, M_MACTEMP);
	free(elements, M_MACTEMP);

	return (error);
}