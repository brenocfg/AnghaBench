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
struct mac {int /*<<< orphan*/  m_buflen; int /*<<< orphan*/  m_string; } ;
struct label {int dummy; } ;
struct ifreq {int dummy; } ;
struct ifnet {int /*<<< orphan*/  if_label; } ;
typedef  int /*<<< orphan*/  mac ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MAC_IFNET_LOCK (struct ifnet*,int) ; 
 int /*<<< orphan*/  MAC_IFNET_UNLOCK (struct ifnet*,int) ; 
 int /*<<< orphan*/  MAC_POLICY_CHECK_NOSLEEP (int /*<<< orphan*/ ,struct ucred*,struct ifnet*,int /*<<< orphan*/ ,struct label*) ; 
 int /*<<< orphan*/  MAC_POLICY_PERFORM_NOSLEEP (int /*<<< orphan*/ ,struct ucred*,struct ifnet*,int /*<<< orphan*/ ,struct label*) ; 
 int MPC_OBJECT_IFNET ; 
 int /*<<< orphan*/  M_MACTEMP ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  PRIV_NET_SETIFMAC ; 
 int copyin (int /*<<< orphan*/ ,struct mac*,int) ; 
 int copyinstr (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ifnet_check_relabel ; 
 int /*<<< orphan*/  ifnet_relabel ; 
 int /*<<< orphan*/  ifr_data_get_ptr (struct ifreq*) ; 
 int mac_check_structmac_consistent (struct mac*) ; 
 int mac_ifnet_internalize_label (struct label*,char*) ; 
 struct label* mac_ifnet_label_alloc () ; 
 int /*<<< orphan*/  mac_ifnet_label_free (struct label*) ; 
 int mac_labeled ; 
 char* malloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int priv_check_cred (struct ucred*,int /*<<< orphan*/ ) ; 

int
mac_ifnet_ioctl_set(struct ucred *cred, struct ifreq *ifr, struct ifnet *ifp)
{
	struct label *intlabel;
	struct mac mac;
	char *buffer;
	int error, locked;

	if (!(mac_labeled & MPC_OBJECT_IFNET))
		return (EINVAL);

	error = copyin(ifr_data_get_ptr(ifr), &mac, sizeof(mac));
	if (error)
		return (error);

	error = mac_check_structmac_consistent(&mac);
	if (error)
		return (error);

	buffer = malloc(mac.m_buflen, M_MACTEMP, M_WAITOK);
	error = copyinstr(mac.m_string, buffer, mac.m_buflen, NULL);
	if (error) {
		free(buffer, M_MACTEMP);
		return (error);
	}

	intlabel = mac_ifnet_label_alloc();
	error = mac_ifnet_internalize_label(intlabel, buffer);
	free(buffer, M_MACTEMP);
	if (error) {
		mac_ifnet_label_free(intlabel);
		return (error);
	}

	/*
	 * XXX: Note that this is a redundant privilege check, since policies
	 * impose this check themselves if required by the policy
	 * Eventually, this should go away.
	 */
	error = priv_check_cred(cred, PRIV_NET_SETIFMAC);
	if (error) {
		mac_ifnet_label_free(intlabel);
		return (error);
	}

	MAC_IFNET_LOCK(ifp, locked);
	MAC_POLICY_CHECK_NOSLEEP(ifnet_check_relabel, cred, ifp,
	    ifp->if_label, intlabel);
	if (error) {
		MAC_IFNET_UNLOCK(ifp, locked);
		mac_ifnet_label_free(intlabel);
		return (error);
	}

	MAC_POLICY_PERFORM_NOSLEEP(ifnet_relabel, cred, ifp, ifp->if_label,
	    intlabel);
	MAC_IFNET_UNLOCK(ifp, locked);

	mac_ifnet_label_free(intlabel);
	return (0);
}