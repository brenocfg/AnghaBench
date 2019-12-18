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
struct wpa_ctrl {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  F_OK ; 
 scalar_t__ access (scalar_t__*,int /*<<< orphan*/ ) ; 
 scalar_t__* client_socket_dir ; 
 struct wpa_ctrl* ctrl_conn ; 
 char* ctrl_iface_dir ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (int) ; 
 int /*<<< orphan*/  perror (scalar_t__*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char const*) ; 
 int strlen (char const*) ; 
 struct wpa_ctrl* wpa_ctrl_open (char const*) ; 
 struct wpa_ctrl* wpa_ctrl_open2 (char*,scalar_t__*) ; 

__attribute__((used)) static struct wpa_ctrl * hostapd_cli_open_connection(const char *ifname)
{
#ifndef CONFIG_CTRL_IFACE_UDP
	char *cfile;
	int flen;
#endif /* !CONFIG_CTRL_IFACE_UDP */

	if (ifname == NULL)
		return NULL;

#ifdef CONFIG_CTRL_IFACE_UDP
	ctrl_conn = wpa_ctrl_open(ifname);
	return ctrl_conn;
#else /* CONFIG_CTRL_IFACE_UDP */
	flen = strlen(ctrl_iface_dir) + strlen(ifname) + 2;
	cfile = malloc(flen);
	if (cfile == NULL)
		return NULL;
	snprintf(cfile, flen, "%s/%s", ctrl_iface_dir, ifname);

	if (client_socket_dir && client_socket_dir[0] &&
	    access(client_socket_dir, F_OK) < 0) {
		perror(client_socket_dir);
		free(cfile);
		return NULL;
	}

	ctrl_conn = wpa_ctrl_open2(cfile, client_socket_dir);
	free(cfile);
	return ctrl_conn;
#endif /* CONFIG_CTRL_IFACE_UDP */
}