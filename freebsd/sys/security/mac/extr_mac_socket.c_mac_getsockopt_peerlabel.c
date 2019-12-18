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
struct socket {int /*<<< orphan*/  so_peerlabel; } ;
struct mac {int /*<<< orphan*/  m_string; int /*<<< orphan*/  m_buflen; } ;
struct label {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int MPC_OBJECT_SOCKET ; 
 int /*<<< orphan*/  M_MACTEMP ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  SOCK_LOCK (struct socket*) ; 
 int /*<<< orphan*/  SOCK_UNLOCK (struct socket*) ; 
 int copyinstr (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int copyout (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  free (char*,int /*<<< orphan*/ ) ; 
 int mac_check_structmac_consistent (struct mac*) ; 
 int mac_labeled ; 
 int /*<<< orphan*/  mac_socket_copy_label (int /*<<< orphan*/ ,struct label*) ; 
 struct label* mac_socket_label_alloc (int) ; 
 int /*<<< orphan*/  mac_socket_label_free (struct label*) ; 
 int mac_socketpeer_externalize_label (struct label*,char*,char*,int /*<<< orphan*/ ) ; 
 char* malloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ strlen (char*) ; 

int
mac_getsockopt_peerlabel(struct ucred *cred, struct socket *so,
    struct mac *mac)
{
	char *elements, *buffer;
	struct label *intlabel;
	int error;

	if (!(mac_labeled & MPC_OBJECT_SOCKET))
		return (EINVAL);

	error = mac_check_structmac_consistent(mac);
	if (error)
		return (error);

	elements = malloc(mac->m_buflen, M_MACTEMP, M_WAITOK);
	error = copyinstr(mac->m_string, elements, mac->m_buflen, NULL);
	if (error) {
		free(elements, M_MACTEMP);
		return (error);
	}

	buffer = malloc(mac->m_buflen, M_MACTEMP, M_WAITOK | M_ZERO);
	intlabel = mac_socket_label_alloc(M_WAITOK);
	SOCK_LOCK(so);
	mac_socket_copy_label(so->so_peerlabel, intlabel);
	SOCK_UNLOCK(so);
	error = mac_socketpeer_externalize_label(intlabel, elements, buffer,
	    mac->m_buflen);
	mac_socket_label_free(intlabel);
	if (error == 0)
		error = copyout(buffer, mac->m_string, strlen(buffer)+1);

	free(buffer, M_MACTEMP);
	free(elements, M_MACTEMP);

	return (error);
}