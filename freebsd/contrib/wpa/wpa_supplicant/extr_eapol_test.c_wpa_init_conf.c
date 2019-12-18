#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct wpa_supplicant {int* bssid; int /*<<< orphan*/  ifname; int /*<<< orphan*/  own_addr; struct eapol_test_data* drv_priv; int /*<<< orphan*/ * driver; } ;
struct hostapd_radius_servers {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  v4; } ;
struct TYPE_8__ {TYPE_2__ u; } ;
struct hostapd_radius_server {int port; int /*<<< orphan*/  shared_secret_len; int /*<<< orphan*/ * shared_secret; TYPE_4__ addr; } ;
struct TYPE_5__ {int /*<<< orphan*/  s_addr; } ;
struct eapol_test_data {int /*<<< orphan*/ * radius; TYPE_3__* radius_conf; TYPE_1__ own_ip_addr; int /*<<< orphan*/  own_addr; } ;
struct TYPE_7__ {int num_auth_servers; int msg_dumps; int force_client_addr; TYPE_4__ client_addr; struct hostapd_radius_server* auth_servers; struct hostapd_radius_server* auth_server; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 int /*<<< orphan*/  RADIUS_AUTH ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  eapol_test_drv_ops ; 
 scalar_t__ hostapd_parse_ip_addr (char const*,TYPE_4__*) ; 
 int /*<<< orphan*/  htonl (int) ; 
 int /*<<< orphan*/  ieee802_1x_receive_auth ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ os_strdup (char const*) ; 
 int /*<<< orphan*/  os_strlcpy (int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  os_strlen (char const*) ; 
 void* os_zalloc (int) ; 
 int /*<<< orphan*/ * radius_client_init (struct wpa_supplicant*,TYPE_3__*) ; 
 int radius_client_register (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct eapol_test_data*) ; 
 int /*<<< orphan*/  sscanf (char const*,char*,int*,int*,int*,int*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,char const*) ; 

__attribute__((used)) static void wpa_init_conf(struct eapol_test_data *e,
			  struct wpa_supplicant *wpa_s, const char *authsrv,
			  int port, const char *secret,
			  const char *cli_addr, const char *ifname)
{
	struct hostapd_radius_server *as;
	int res;

	wpa_s->driver = &eapol_test_drv_ops;
	wpa_s->drv_priv = e;
	wpa_s->bssid[5] = 1;
	os_memcpy(wpa_s->own_addr, e->own_addr, ETH_ALEN);
	e->own_ip_addr.s_addr = htonl((127 << 24) | 1);
	os_strlcpy(wpa_s->ifname, ifname, sizeof(wpa_s->ifname));

	e->radius_conf = os_zalloc(sizeof(struct hostapd_radius_servers));
	assert(e->radius_conf != NULL);
	e->radius_conf->num_auth_servers = 1;
	as = os_zalloc(sizeof(struct hostapd_radius_server));
	assert(as != NULL);
#if defined(CONFIG_NATIVE_WINDOWS) || defined(CONFIG_ANSI_C_EXTRA)
	{
		int a[4];
		u8 *pos;
		sscanf(authsrv, "%d.%d.%d.%d", &a[0], &a[1], &a[2], &a[3]);
		pos = (u8 *) &as->addr.u.v4;
		*pos++ = a[0];
		*pos++ = a[1];
		*pos++ = a[2];
		*pos++ = a[3];
	}
#else /* CONFIG_NATIVE_WINDOWS or CONFIG_ANSI_C_EXTRA */
	if (hostapd_parse_ip_addr(authsrv, &as->addr) < 0) {
		wpa_printf(MSG_ERROR, "Invalid IP address '%s'",
			   authsrv);
		assert(0);
	}
#endif /* CONFIG_NATIVE_WINDOWS or CONFIG_ANSI_C_EXTRA */
	as->port = port;
	as->shared_secret = (u8 *) os_strdup(secret);
	as->shared_secret_len = os_strlen(secret);
	e->radius_conf->auth_server = as;
	e->radius_conf->auth_servers = as;
	e->radius_conf->msg_dumps = 1;
	if (cli_addr) {
		if (hostapd_parse_ip_addr(cli_addr,
					  &e->radius_conf->client_addr) == 0)
			e->radius_conf->force_client_addr = 1;
		else {
			wpa_printf(MSG_ERROR, "Invalid IP address '%s'",
				   cli_addr);
			assert(0);
		}
	}

	e->radius = radius_client_init(wpa_s, e->radius_conf);
	assert(e->radius != NULL);

	res = radius_client_register(e->radius, RADIUS_AUTH,
				     ieee802_1x_receive_auth, e);
	assert(res == 0);
}