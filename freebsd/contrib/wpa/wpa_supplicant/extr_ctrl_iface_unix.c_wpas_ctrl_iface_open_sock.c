#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct wpa_supplicant {char* ifname; TYPE_1__* conf; } ;
struct sockaddr_un {int sun_len; int /*<<< orphan*/  sun_path; int /*<<< orphan*/  sun_family; } ;
struct sockaddr {int dummy; } ;
struct group {scalar_t__ gr_gid; } ;
struct ctrl_iface_priv {int sock; int android_control_socket; } ;
typedef  scalar_t__ gid_t ;
typedef  int /*<<< orphan*/  addr ;
struct TYPE_2__ {char* ctrl_interface_group; int /*<<< orphan*/  ctrl_interface; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_UNIX ; 
 scalar_t__ EEXIST ; 
 int /*<<< orphan*/  F_GETFL ; 
 int /*<<< orphan*/  F_SETFL ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 int /*<<< orphan*/  MSG_INFO ; 
 int O_NONBLOCK ; 
 int /*<<< orphan*/  PF_UNIX ; 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 int S_IRGRP ; 
 int S_IRUSR ; 
 int S_IRWXG ; 
 int S_IRWXU ; 
 int S_IWUSR ; 
 int S_IXGRP ; 
 int S_IXUSR ; 
 int android_get_control_socket (int /*<<< orphan*/ ) ; 
 scalar_t__ bind (int,struct sockaddr*,int) ; 
 scalar_t__ chmod (char*,int) ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ connect (int,struct sockaddr*,int) ; 
 int /*<<< orphan*/  eloop_register_read_sock (int,int /*<<< orphan*/ ,struct wpa_supplicant*,struct ctrl_iface_priv*) ; 
 scalar_t__ errno ; 
 scalar_t__ fcntl (int,int /*<<< orphan*/ ,...) ; 
 struct group* getgrnam (char*) ; 
 scalar_t__ lchown (char*,int,scalar_t__) ; 
 scalar_t__ mkdir (char*,int) ; 
 int /*<<< orphan*/  os_free (char*) ; 
 int /*<<< orphan*/  os_memset (struct sockaddr_un*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  os_snprintf (int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ) ; 
 char* os_strdup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_strlcpy (int /*<<< orphan*/ ,char*,int) ; 
 int os_strlen (char*) ; 
 scalar_t__ os_strncmp (char*,char*,int) ; 
 char* os_strstr (char*,char*) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* strerror (scalar_t__) ; 
 scalar_t__ strtol (char*,char**,int) ; 
 scalar_t__ unlink (char*) ; 
 int /*<<< orphan*/  wpa_msg_register_cb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  wpa_supplicant_ctrl_iface_msg_cb ; 
 char* wpa_supplicant_ctrl_iface_path (struct wpa_supplicant*) ; 
 int /*<<< orphan*/  wpa_supplicant_ctrl_iface_receive ; 

__attribute__((used)) static int wpas_ctrl_iface_open_sock(struct wpa_supplicant *wpa_s,
				     struct ctrl_iface_priv *priv)
{
	struct sockaddr_un addr;
	char *fname = NULL;
	gid_t gid = 0;
	int gid_set = 0;
	char *buf, *dir = NULL, *gid_str = NULL;
	struct group *grp;
	char *endp;
	int flags;

	buf = os_strdup(wpa_s->conf->ctrl_interface);
	if (buf == NULL)
		goto fail;
#ifdef ANDROID
	os_snprintf(addr.sun_path, sizeof(addr.sun_path), "wpa_%s",
		    wpa_s->conf->ctrl_interface);
	priv->sock = android_get_control_socket(addr.sun_path);
	if (priv->sock >= 0) {
		priv->android_control_socket = 1;
		goto havesock;
	}
#endif /* ANDROID */
	if (os_strncmp(buf, "DIR=", 4) == 0) {
		dir = buf + 4;
		gid_str = os_strstr(dir, " GROUP=");
		if (gid_str) {
			*gid_str = '\0';
			gid_str += 7;
		}
	} else {
		dir = buf;
		gid_str = wpa_s->conf->ctrl_interface_group;
	}

	if (mkdir(dir, S_IRWXU | S_IRWXG) < 0) {
		if (errno == EEXIST) {
			wpa_printf(MSG_DEBUG, "Using existing control "
				   "interface directory.");
		} else {
			wpa_printf(MSG_ERROR, "mkdir[ctrl_interface=%s]: %s",
				   dir, strerror(errno));
			goto fail;
		}
	}

#ifdef ANDROID
	/*
	 * wpa_supplicant is started from /init.*.rc on Android and that seems
	 * to be using umask 0077 which would leave the control interface
	 * directory without group access. This breaks things since Wi-Fi
	 * framework assumes that this directory can be accessed by other
	 * applications in the wifi group. Fix this by adding group access even
	 * if umask value would prevent this.
	 */
	if (chmod(dir, S_IRWXU | S_IRWXG) < 0) {
		wpa_printf(MSG_ERROR, "CTRL: Could not chmod directory: %s",
			   strerror(errno));
		/* Try to continue anyway */
	}
#endif /* ANDROID */

	if (gid_str) {
		grp = getgrnam(gid_str);
		if (grp) {
			gid = grp->gr_gid;
			gid_set = 1;
			wpa_printf(MSG_DEBUG, "ctrl_interface_group=%d"
				   " (from group name '%s')",
				   (int) gid, gid_str);
		} else {
			/* Group name not found - try to parse this as gid */
			gid = strtol(gid_str, &endp, 10);
			if (*gid_str == '\0' || *endp != '\0') {
				wpa_printf(MSG_ERROR, "CTRL: Invalid group "
					   "'%s'", gid_str);
				goto fail;
			}
			gid_set = 1;
			wpa_printf(MSG_DEBUG, "ctrl_interface_group=%d",
				   (int) gid);
		}
	}

	if (gid_set && lchown(dir, -1, gid) < 0) {
		wpa_printf(MSG_ERROR, "lchown[ctrl_interface=%s,gid=%d]: %s",
			   dir, (int) gid, strerror(errno));
		goto fail;
	}

	/* Make sure the group can enter and read the directory */
	if (gid_set &&
	    chmod(dir, S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IXGRP) < 0) {
		wpa_printf(MSG_ERROR, "CTRL: chmod[ctrl_interface]: %s",
			   strerror(errno));
		goto fail;
	}

	if (os_strlen(dir) + 1 + os_strlen(wpa_s->ifname) >=
	    sizeof(addr.sun_path)) {
		wpa_printf(MSG_ERROR, "ctrl_iface path limit exceeded");
		goto fail;
	}

	priv->sock = socket(PF_UNIX, SOCK_DGRAM, 0);
	if (priv->sock < 0) {
		wpa_printf(MSG_ERROR, "socket(PF_UNIX): %s", strerror(errno));
		goto fail;
	}

	os_memset(&addr, 0, sizeof(addr));
#if defined(__FreeBSD__) || defined(__FreeBSD_kernel__)
	addr.sun_len = sizeof(addr);
#endif /* __FreeBSD__ */
	addr.sun_family = AF_UNIX;
	fname = wpa_supplicant_ctrl_iface_path(wpa_s);
	if (fname == NULL)
		goto fail;
	os_strlcpy(addr.sun_path, fname, sizeof(addr.sun_path));
	if (bind(priv->sock, (struct sockaddr *) &addr, sizeof(addr)) < 0) {
		wpa_printf(MSG_DEBUG, "ctrl_iface bind(PF_UNIX) failed: %s",
			   strerror(errno));
		if (connect(priv->sock, (struct sockaddr *) &addr,
			    sizeof(addr)) < 0) {
			wpa_printf(MSG_DEBUG, "ctrl_iface exists, but does not"
				   " allow connections - assuming it was left"
				   "over from forced program termination");
			if (unlink(fname) < 0) {
				wpa_printf(MSG_ERROR,
					   "Could not unlink existing ctrl_iface socket '%s': %s",
					   fname, strerror(errno));
				goto fail;
			}
			if (bind(priv->sock, (struct sockaddr *) &addr,
				 sizeof(addr)) < 0) {
				wpa_printf(MSG_ERROR, "supp-ctrl-iface-init: bind(PF_UNIX): %s",
					   strerror(errno));
				goto fail;
			}
			wpa_printf(MSG_DEBUG, "Successfully replaced leftover "
				   "ctrl_iface socket '%s'", fname);
		} else {
			wpa_printf(MSG_INFO, "ctrl_iface exists and seems to "
				   "be in use - cannot override it");
			wpa_printf(MSG_INFO, "Delete '%s' manually if it is "
				   "not used anymore", fname);
			os_free(fname);
			fname = NULL;
			goto fail;
		}
	}

	if (gid_set && lchown(fname, -1, gid) < 0) {
		wpa_printf(MSG_ERROR, "lchown[ctrl_interface=%s,gid=%d]: %s",
			   fname, (int) gid, strerror(errno));
		goto fail;
	}

	if (chmod(fname, S_IRWXU | S_IRWXG) < 0) {
		wpa_printf(MSG_ERROR, "chmod[ctrl_interface=%s]: %s",
			   fname, strerror(errno));
		goto fail;
	}
	os_free(fname);

#ifdef ANDROID
havesock:
#endif /* ANDROID */

	/*
	 * Make socket non-blocking so that we don't hang forever if
	 * target dies unexpectedly.
	 */
	flags = fcntl(priv->sock, F_GETFL);
	if (flags >= 0) {
		flags |= O_NONBLOCK;
		if (fcntl(priv->sock, F_SETFL, flags) < 0) {
			wpa_printf(MSG_INFO, "fcntl(ctrl, O_NONBLOCK): %s",
				   strerror(errno));
			/* Not fatal, continue on.*/
		}
	}

	eloop_register_read_sock(priv->sock, wpa_supplicant_ctrl_iface_receive,
				 wpa_s, priv);
	wpa_msg_register_cb(wpa_supplicant_ctrl_iface_msg_cb);

	os_free(buf);
	return 0;

fail:
	if (priv->sock >= 0) {
		close(priv->sock);
		priv->sock = -1;
	}
	if (fname) {
		unlink(fname);
		os_free(fname);
	}
	os_free(buf);
	return -1;
}