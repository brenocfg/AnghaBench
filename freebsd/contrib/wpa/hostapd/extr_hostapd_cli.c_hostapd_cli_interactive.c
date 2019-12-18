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

/* Variables and functions */
 char* CONFIG_HOSTAPD_CLI_HISTORY_DIR ; 
 int /*<<< orphan*/  cli_txt_list_flush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  edit_deinit (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  edit_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  eloop_cancel_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  eloop_register_signal_terminate (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  eloop_register_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  eloop_run () ; 
 char* getenv (char*) ; 
 int /*<<< orphan*/  hostapd_cli_edit_cmd_cb ; 
 int /*<<< orphan*/  hostapd_cli_edit_completion_cb ; 
 int /*<<< orphan*/  hostapd_cli_edit_eof_cb ; 
 int /*<<< orphan*/  hostapd_cli_eloop_terminate ; 
 int /*<<< orphan*/  hostapd_cli_ping ; 
 int /*<<< orphan*/  os_free (char*) ; 
 char* os_malloc (int) ; 
 int /*<<< orphan*/  os_snprintf (char*,int,char*,char*,char const*) ; 
 int os_strlen (char const*) ; 
 int /*<<< orphan*/  ping_interval ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  stations ; 

__attribute__((used)) static void hostapd_cli_interactive(void)
{
	char *hfile = NULL;
	char *home;

	printf("\nInteractive mode\n\n");

#ifdef CONFIG_HOSTAPD_CLI_HISTORY_DIR
	home = CONFIG_HOSTAPD_CLI_HISTORY_DIR;
#else /* CONFIG_HOSTAPD_CLI_HISTORY_DIR */
	home = getenv("HOME");
#endif /* CONFIG_HOSTAPD_CLI_HISTORY_DIR */
	if (home) {
		const char *fname = ".hostapd_cli_history";
		int hfile_len = os_strlen(home) + 1 + os_strlen(fname) + 1;
		hfile = os_malloc(hfile_len);
		if (hfile)
			os_snprintf(hfile, hfile_len, "%s/%s", home, fname);
	}

	eloop_register_signal_terminate(hostapd_cli_eloop_terminate, NULL);
	edit_init(hostapd_cli_edit_cmd_cb, hostapd_cli_edit_eof_cb,
		  hostapd_cli_edit_completion_cb, NULL, hfile, NULL);
	eloop_register_timeout(ping_interval, 0, hostapd_cli_ping, NULL, NULL);

	eloop_run();

	cli_txt_list_flush(&stations);
	edit_deinit(hfile, NULL);
	os_free(hfile);
	eloop_cancel_timeout(hostapd_cli_ping, NULL, NULL);
}