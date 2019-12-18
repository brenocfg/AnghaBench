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
typedef  int /*<<< orphan*/  u8 ;
struct wpa_global {scalar_t__ p2p_init_wpa_s; } ;

/* Variables and functions */
 int MSG_DEBUG ; 
 int MSG_EXCESSIVE ; 
 int fst_ctrl_iface_receive (char*,char*,int const) ; 
 int /*<<< orphan*/  os_free (char*) ; 
 char* os_malloc (int const) ; 
 int /*<<< orphan*/  os_memcpy (char*,char*,int) ; 
 char* os_strchr (char*,char) ; 
 scalar_t__ os_strcmp (char*,char*) ; 
 int /*<<< orphan*/  os_strlen (char*) ; 
 scalar_t__ os_strncmp (char*,char*,int) ; 
 scalar_t__ wpa_debug_reopen_file () ; 
 int /*<<< orphan*/  wpa_hexdump_ascii (int,char*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 char* wpa_supplicant_ctrl_iface_process (scalar_t__,char*,size_t*) ; 
 scalar_t__ wpa_supplicant_global_iface_add (struct wpa_global*,char*) ; 
 int wpa_supplicant_global_iface_interfaces (struct wpa_global*,char*,char*,int const) ; 
 int wpa_supplicant_global_iface_list (struct wpa_global*,char*,int const) ; 
 scalar_t__ wpa_supplicant_global_iface_remove (struct wpa_global*,char*) ; 
 int /*<<< orphan*/  wpa_supplicant_terminate_proc (struct wpa_global*) ; 
 scalar_t__ wpas_global_ctrl_iface_dup_network (struct wpa_global*,char*) ; 
 int wpas_global_ctrl_iface_fst_attach (struct wpa_global*,char*,char*,int const) ; 
 int wpas_global_ctrl_iface_fst_detach (struct wpa_global*,char*,char*,int const) ; 
 char* wpas_global_ctrl_iface_ifname (struct wpa_global*,char*,char*,size_t*) ; 
 char* wpas_global_ctrl_iface_redir (struct wpa_global*,char*,size_t*) ; 
 scalar_t__ wpas_global_ctrl_iface_save_config (struct wpa_global*) ; 
 scalar_t__ wpas_global_ctrl_iface_set (struct wpa_global*,char*) ; 
 int wpas_global_ctrl_iface_status (struct wpa_global*,char*,int const) ; 
 scalar_t__ wpas_module_tests () ; 
 int /*<<< orphan*/  wpas_notify_resume (struct wpa_global*) ; 
 int /*<<< orphan*/  wpas_notify_suspend (struct wpa_global*) ; 

char * wpa_supplicant_global_ctrl_iface_process(struct wpa_global *global,
						char *buf, size_t *resp_len)
{
	char *reply;
	const int reply_size = 2048;
	int reply_len;
	int level = MSG_DEBUG;

	if (os_strncmp(buf, "IFNAME=", 7) == 0) {
		char *pos = os_strchr(buf + 7, ' ');
		if (pos) {
			*pos++ = '\0';
			return wpas_global_ctrl_iface_ifname(global,
							     buf + 7, pos,
							     resp_len);
		}
	}

	reply = wpas_global_ctrl_iface_redir(global, buf, resp_len);
	if (reply)
		return reply;

	if (os_strcmp(buf, "PING") == 0)
		level = MSG_EXCESSIVE;
	wpa_hexdump_ascii(level, "RX global ctrl_iface",
			  (const u8 *) buf, os_strlen(buf));

	reply = os_malloc(reply_size);
	if (reply == NULL) {
		*resp_len = 1;
		return NULL;
	}

	os_memcpy(reply, "OK\n", 3);
	reply_len = 3;

	if (os_strcmp(buf, "PING") == 0) {
		os_memcpy(reply, "PONG\n", 5);
		reply_len = 5;
	} else if (os_strncmp(buf, "INTERFACE_ADD ", 14) == 0) {
		if (wpa_supplicant_global_iface_add(global, buf + 14))
			reply_len = -1;
	} else if (os_strncmp(buf, "INTERFACE_REMOVE ", 17) == 0) {
		if (wpa_supplicant_global_iface_remove(global, buf + 17))
			reply_len = -1;
	} else if (os_strcmp(buf, "INTERFACE_LIST") == 0) {
		reply_len = wpa_supplicant_global_iface_list(
			global, reply, reply_size);
	} else if (os_strncmp(buf, "INTERFACES", 10) == 0) {
		reply_len = wpa_supplicant_global_iface_interfaces(
			global, buf + 10, reply, reply_size);
#ifdef CONFIG_FST
	} else if (os_strncmp(buf, "FST-ATTACH ", 11) == 0) {
		reply_len = wpas_global_ctrl_iface_fst_attach(global, buf + 11,
							      reply,
							      reply_size);
	} else if (os_strncmp(buf, "FST-DETACH ", 11) == 0) {
		reply_len = wpas_global_ctrl_iface_fst_detach(global, buf + 11,
							      reply,
							      reply_size);
	} else if (os_strncmp(buf, "FST-MANAGER ", 12) == 0) {
		reply_len = fst_ctrl_iface_receive(buf + 12, reply, reply_size);
#endif /* CONFIG_FST */
	} else if (os_strcmp(buf, "TERMINATE") == 0) {
		wpa_supplicant_terminate_proc(global);
	} else if (os_strcmp(buf, "SUSPEND") == 0) {
		wpas_notify_suspend(global);
	} else if (os_strcmp(buf, "RESUME") == 0) {
		wpas_notify_resume(global);
	} else if (os_strncmp(buf, "SET ", 4) == 0) {
		if (wpas_global_ctrl_iface_set(global, buf + 4)) {
#ifdef CONFIG_P2P
			if (global->p2p_init_wpa_s) {
				os_free(reply);
				/* Check if P2P redirection would work for this
				 * command. */
				return wpa_supplicant_ctrl_iface_process(
					global->p2p_init_wpa_s,
					buf, resp_len);
			}
#endif /* CONFIG_P2P */
			reply_len = -1;
		}
	} else if (os_strncmp(buf, "DUP_NETWORK ", 12) == 0) {
		if (wpas_global_ctrl_iface_dup_network(global, buf + 12))
			reply_len = -1;
#ifndef CONFIG_NO_CONFIG_WRITE
	} else if (os_strcmp(buf, "SAVE_CONFIG") == 0) {
		if (wpas_global_ctrl_iface_save_config(global))
			reply_len = -1;
#endif /* CONFIG_NO_CONFIG_WRITE */
	} else if (os_strcmp(buf, "STATUS") == 0) {
		reply_len = wpas_global_ctrl_iface_status(global, reply,
							  reply_size);
#ifdef CONFIG_MODULE_TESTS
	} else if (os_strcmp(buf, "MODULE_TESTS") == 0) {
		if (wpas_module_tests() < 0)
			reply_len = -1;
#endif /* CONFIG_MODULE_TESTS */
	} else if (os_strncmp(buf, "RELOG", 5) == 0) {
		if (wpa_debug_reopen_file() < 0)
			reply_len = -1;
	} else {
		os_memcpy(reply, "UNKNOWN COMMAND\n", 16);
		reply_len = 16;
	}

	if (reply_len < 0) {
		os_memcpy(reply, "FAIL\n", 5);
		reply_len = 5;
	}

	*resp_len = reply_len;
	return reply;
}