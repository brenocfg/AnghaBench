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
struct in_addr {int /*<<< orphan*/  s_addr; } ;
struct http_server {int dummy; } ;
struct browser_data {int success; } ;
typedef  scalar_t__ pid_t ;
typedef  int /*<<< orphan*/  data ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_ERROR ; 
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/  browser_timeout ; 
 int /*<<< orphan*/  eloop_cancel_timeout (int /*<<< orphan*/ ,struct browser_data*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  eloop_destroy () ; 
 scalar_t__ eloop_init () ; 
 int /*<<< orphan*/  eloop_register_timeout (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct browser_data*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  eloop_run () ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  execv (char*,char**) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 scalar_t__ fork () ; 
 int /*<<< orphan*/  htonl (int) ; 
 int /*<<< orphan*/  http_req ; 
 int /*<<< orphan*/  http_server_deinit (struct http_server*) ; 
 struct http_server* http_server_init (struct in_addr*,int,int /*<<< orphan*/ ,struct browser_data*) ; 
 int /*<<< orphan*/  os_memset (struct browser_data*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 scalar_t__ system (char*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

int hs20_web_browser(const char *url)
{
	struct http_server *http;
	struct in_addr addr;
	struct browser_data data;
	pid_t pid;

	wpa_printf(MSG_INFO, "Launching Android browser to %s", url);

	os_memset(&data, 0, sizeof(data));

	if (eloop_init() < 0) {
		wpa_printf(MSG_ERROR, "eloop_init failed");
		return -1;
	}
	addr.s_addr = htonl((127 << 24) | 1);
	http = http_server_init(&addr, 12345, http_req, &data);
	if (http == NULL) {
		wpa_printf(MSG_ERROR, "http_server_init failed");
		eloop_destroy();
		return -1;
	}

	pid = fork();
	if (pid < 0) {
		wpa_printf(MSG_ERROR, "fork: %s", strerror(errno));
		http_server_deinit(http);
		eloop_destroy();
		return -1;
	}

	if (pid == 0) {
		/* run the external command in the child process */
		char *argv[7];

		argv[0] = "browser-android";
		argv[1] = "start";
		argv[2] = "-a";
		argv[3] = "android.intent.action.VIEW";
		argv[4] = "-d";
		argv[5] = (void *) url;
		argv[6] = NULL;

		execv("/system/bin/am", argv);
		wpa_printf(MSG_ERROR, "execv: %s", strerror(errno));
		exit(0);
		return -1;
	}

	eloop_register_timeout(30, 0, browser_timeout, &data, NULL);
	eloop_run();
	eloop_cancel_timeout(browser_timeout, &data, NULL);
	http_server_deinit(http);
	eloop_destroy();

	wpa_printf(MSG_INFO, "Closing Android browser");
	if (system("/system/bin/input keyevent KEYCODE_HOME") != 0) {
		wpa_printf(MSG_INFO, "Failed to inject keyevent");
	}

	return data.success;
}