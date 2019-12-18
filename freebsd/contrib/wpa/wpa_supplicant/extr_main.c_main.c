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
struct wpa_supplicant {int dummy; } ;
struct wpa_params {int dbus_ctrl_interface; int match_iface_count; struct wpa_params* pid_file; struct wpa_params* match_ifaces; int /*<<< orphan*/ * ctrl_interface; int /*<<< orphan*/ * ifname; int /*<<< orphan*/ * confname; int /*<<< orphan*/  wait_for_monitor; int /*<<< orphan*/  wpa_debug_timestamp; int /*<<< orphan*/  wpa_debug_tracing; int /*<<< orphan*/  wpa_debug_syslog; int /*<<< orphan*/  wpa_debug_level; void* driver_param; void* override_ctrl_interface; void* override_driver; void* conf_p2p_dev; int /*<<< orphan*/  wpa_debug_show_keys; void* confanother; void* ctrl_interface_group; void* wpa_debug_file_path; void* entropy_file; void* driver; int /*<<< orphan*/  daemonize; void* bridge_ifname; } ;
struct wpa_interface {int dbus_ctrl_interface; int match_iface_count; struct wpa_interface* pid_file; struct wpa_interface* match_ifaces; int /*<<< orphan*/ * ctrl_interface; int /*<<< orphan*/ * ifname; int /*<<< orphan*/ * confname; int /*<<< orphan*/  wait_for_monitor; int /*<<< orphan*/  wpa_debug_timestamp; int /*<<< orphan*/  wpa_debug_tracing; int /*<<< orphan*/  wpa_debug_syslog; int /*<<< orphan*/  wpa_debug_level; void* driver_param; void* override_ctrl_interface; void* override_driver; void* conf_p2p_dev; int /*<<< orphan*/  wpa_debug_show_keys; void* confanother; void* ctrl_interface_group; void* wpa_debug_file_path; void* entropy_file; void* driver; int /*<<< orphan*/  daemonize; void* bridge_ifname; } ;
struct wpa_global {int dummy; } ;
typedef  int /*<<< orphan*/  params ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_ERROR ; 
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/  MSG_WARNING ; 
 int /*<<< orphan*/  fst_ctrl_cli ; 
 int /*<<< orphan*/  fst_global_add_ctrl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fst_global_deinit () ; 
 scalar_t__ fst_global_init () ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  license () ; 
 void* optarg ; 
 int /*<<< orphan*/  os_free (struct wpa_params*) ; 
 int /*<<< orphan*/  os_memset (struct wpa_params*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  os_program_deinit () ; 
 scalar_t__ os_program_init () ; 
 struct wpa_params* os_realloc_array (struct wpa_params*,int,int) ; 
 struct wpa_params* os_rel2abs_path (void*) ; 
 struct wpa_params* os_zalloc (int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  usage () ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 struct wpa_supplicant* wpa_supplicant_add_iface (struct wpa_global*,struct wpa_params*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpa_supplicant_deinit (struct wpa_global*) ; 
 int /*<<< orphan*/  wpa_supplicant_fd_workaround (int) ; 
 struct wpa_global* wpa_supplicant_init (struct wpa_params*) ; 
 int wpa_supplicant_init_match (struct wpa_global*) ; 
 int wpa_supplicant_run (struct wpa_global*) ; 
 char* wpa_supplicant_version ; 

int main(int argc, char *argv[])
{
	int c, i;
	struct wpa_interface *ifaces, *iface;
	int iface_count, exitcode = -1;
	struct wpa_params params;
	struct wpa_global *global;

	if (os_program_init())
		return -1;

	os_memset(&params, 0, sizeof(params));
	params.wpa_debug_level = MSG_INFO;

	iface = ifaces = os_zalloc(sizeof(struct wpa_interface));
	if (ifaces == NULL)
		return -1;
	iface_count = 1;

	wpa_supplicant_fd_workaround(1);

#ifdef CONFIG_DRIVER_NDIS
	void driver_ndis_init_ops(void);
	driver_ndis_init_ops();
#endif /* CONFIG_DRIVER_NDIS */

	for (;;) {
		c = getopt(argc, argv,
			   "b:Bc:C:D:de:f:g:G:hi:I:KLMm:No:O:p:P:qsTtuvW");
		if (c < 0)
			break;
		switch (c) {
		case 'b':
			iface->bridge_ifname = optarg;
			break;
		case 'B':
			params.daemonize++;
			break;
		case 'c':
			iface->confname = optarg;
			break;
		case 'C':
			iface->ctrl_interface = optarg;
			break;
		case 'D':
			iface->driver = optarg;
			break;
		case 'd':
#ifdef CONFIG_NO_STDOUT_DEBUG
			printf("Debugging disabled with "
			       "CONFIG_NO_STDOUT_DEBUG=y build time "
			       "option.\n");
			goto out;
#else /* CONFIG_NO_STDOUT_DEBUG */
			params.wpa_debug_level--;
			break;
#endif /* CONFIG_NO_STDOUT_DEBUG */
		case 'e':
			params.entropy_file = optarg;
			break;
#ifdef CONFIG_DEBUG_FILE
		case 'f':
			params.wpa_debug_file_path = optarg;
			break;
#endif /* CONFIG_DEBUG_FILE */
		case 'g':
			params.ctrl_interface = optarg;
			break;
		case 'G':
			params.ctrl_interface_group = optarg;
			break;
		case 'h':
			usage();
			exitcode = 0;
			goto out;
		case 'i':
			iface->ifname = optarg;
			break;
		case 'I':
			iface->confanother = optarg;
			break;
		case 'K':
			params.wpa_debug_show_keys++;
			break;
		case 'L':
			license();
			exitcode = 0;
			goto out;
#ifdef CONFIG_P2P
		case 'm':
			params.conf_p2p_dev = optarg;
			break;
#endif /* CONFIG_P2P */
		case 'o':
			params.override_driver = optarg;
			break;
		case 'O':
			params.override_ctrl_interface = optarg;
			break;
		case 'p':
			iface->driver_param = optarg;
			break;
		case 'P':
			os_free(params.pid_file);
			params.pid_file = os_rel2abs_path(optarg);
			break;
		case 'q':
			params.wpa_debug_level++;
			break;
#ifdef CONFIG_DEBUG_SYSLOG
		case 's':
			params.wpa_debug_syslog++;
			break;
#endif /* CONFIG_DEBUG_SYSLOG */
#ifdef CONFIG_DEBUG_LINUX_TRACING
		case 'T':
			params.wpa_debug_tracing++;
			break;
#endif /* CONFIG_DEBUG_LINUX_TRACING */
		case 't':
			params.wpa_debug_timestamp++;
			break;
#ifdef CONFIG_CTRL_IFACE_DBUS_NEW
		case 'u':
			params.dbus_ctrl_interface = 1;
			break;
#endif /* CONFIG_CTRL_IFACE_DBUS_NEW */
		case 'v':
			printf("%s\n", wpa_supplicant_version);
			exitcode = 0;
			goto out;
		case 'W':
			params.wait_for_monitor++;
			break;
#ifdef CONFIG_MATCH_IFACE
		case 'M':
			params.match_iface_count++;
			iface = os_realloc_array(params.match_ifaces,
						 params.match_iface_count,
						 sizeof(struct wpa_interface));
			if (!iface)
				goto out;
			params.match_ifaces = iface;
			iface = &params.match_ifaces[params.match_iface_count -
						     1];
			os_memset(iface, 0, sizeof(*iface));
			break;
#endif /* CONFIG_MATCH_IFACE */
		case 'N':
			iface_count++;
			iface = os_realloc_array(ifaces, iface_count,
						 sizeof(struct wpa_interface));
			if (iface == NULL)
				goto out;
			ifaces = iface;
			iface = &ifaces[iface_count - 1];
			os_memset(iface, 0, sizeof(*iface));
			break;
		default:
			usage();
			exitcode = 0;
			goto out;
		}
	}

	exitcode = 0;
	global = wpa_supplicant_init(&params);
	if (global == NULL) {
		wpa_printf(MSG_ERROR, "Failed to initialize wpa_supplicant");
		exitcode = -1;
		goto out;
	} else {
		wpa_printf(MSG_INFO, "Successfully initialized "
			   "wpa_supplicant");
	}

	if (fst_global_init()) {
		wpa_printf(MSG_ERROR, "Failed to initialize FST");
		exitcode = -1;
		goto out;
	}

#if defined(CONFIG_FST) && defined(CONFIG_CTRL_IFACE)
	if (!fst_global_add_ctrl(fst_ctrl_cli))
		wpa_printf(MSG_WARNING, "Failed to add CLI FST ctrl");
#endif

	for (i = 0; exitcode == 0 && i < iface_count; i++) {
		struct wpa_supplicant *wpa_s;

		if ((ifaces[i].confname == NULL &&
		     ifaces[i].ctrl_interface == NULL) ||
		    ifaces[i].ifname == NULL) {
			if (iface_count == 1 && (params.ctrl_interface ||
#ifdef CONFIG_MATCH_IFACE
						 params.match_iface_count ||
#endif /* CONFIG_MATCH_IFACE */
						 params.dbus_ctrl_interface))
				break;
			usage();
			exitcode = -1;
			break;
		}
		wpa_s = wpa_supplicant_add_iface(global, &ifaces[i], NULL);
		if (wpa_s == NULL) {
			exitcode = -1;
			break;
		}
	}

#ifdef CONFIG_MATCH_IFACE
	if (exitcode == 0)
		exitcode = wpa_supplicant_init_match(global);
#endif /* CONFIG_MATCH_IFACE */

	if (exitcode == 0)
		exitcode = wpa_supplicant_run(global);

	wpa_supplicant_deinit(global);

	fst_global_deinit();

out:
	wpa_supplicant_fd_workaround(0);
	os_free(ifaces);
#ifdef CONFIG_MATCH_IFACE
	os_free(params.match_ifaces);
#endif /* CONFIG_MATCH_IFACE */
	os_free(params.pid_file);

	os_program_deinit();

	return exitcode;
}