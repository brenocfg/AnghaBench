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
typedef  int /*<<< orphan*/  u8 ;
struct l2_packet_data {void (* rx_callback ) (void*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,size_t) ;int l2_hdr; int /*<<< orphan*/ * rx_avail; int /*<<< orphan*/  own_addr; void* rx_callback_ctx; int /*<<< orphan*/  ifname; } ;
struct TYPE_2__ {unsigned short first_proto; int refcount; int /*<<< orphan*/ * stop_request; int /*<<< orphan*/ * rx_thread; int /*<<< orphan*/ * rx_processed; int /*<<< orphan*/ * ready_for_read; struct l2_packet_data** l2; } ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ *) ; 
 void* CreateEvent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * CreateThread (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct l2_packet_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/ * TEXT (char*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  eloop_register_event (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,struct l2_packet_data*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  eloop_unregister_event (int /*<<< orphan*/ *,int) ; 
 TYPE_1__* l2_ndisuio_global ; 
 scalar_t__ l2_ndisuio_set_ether_type (unsigned short) ; 
 int /*<<< orphan*/  l2_ndisuio_start_read (struct l2_packet_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l2_packet_rx_event ; 
 int /*<<< orphan*/  l2_packet_rx_thread ; 
 int /*<<< orphan*/  os_free (struct l2_packet_data*) ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_strlcpy (int /*<<< orphan*/ ,char const*,int) ; 
 void* os_zalloc (int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

struct l2_packet_data * l2_packet_init(
	const char *ifname, const u8 *own_addr, unsigned short protocol,
	void (*rx_callback)(void *ctx, const u8 *src_addr,
			    const u8 *buf, size_t len),
	void *rx_callback_ctx, int l2_hdr)
{
	struct l2_packet_data *l2;

	if (l2_ndisuio_global == NULL) {
		l2_ndisuio_global = os_zalloc(sizeof(*l2_ndisuio_global));
		if (l2_ndisuio_global == NULL)
			return NULL;
		l2_ndisuio_global->first_proto = protocol;
	}
	if (l2_ndisuio_global->refcount >= 2) {
		wpa_printf(MSG_ERROR, "L2(NDISUIO): Not more than two "
			   "simultaneous connections allowed");
		return NULL;
	}
	l2_ndisuio_global->refcount++;

	l2 = os_zalloc(sizeof(struct l2_packet_data));
	if (l2 == NULL)
		return NULL;
	l2_ndisuio_global->l2[l2_ndisuio_global->refcount - 1] = l2;

	os_strlcpy(l2->ifname, ifname, sizeof(l2->ifname));
	l2->rx_callback = rx_callback;
	l2->rx_callback_ctx = rx_callback_ctx;
	l2->l2_hdr = l2_hdr;

	if (own_addr)
		os_memcpy(l2->own_addr, own_addr, ETH_ALEN);

	if (l2_ndisuio_set_ether_type(protocol) < 0) {
		os_free(l2);
		return NULL;
	}

	if (l2_ndisuio_global->refcount > 1) {
		wpa_printf(MSG_DEBUG, "L2(NDISUIO): Temporarily setting "
			   "filtering ethertype to %04x", protocol);
		if (l2_ndisuio_global->l2[0])
			l2->rx_avail = l2_ndisuio_global->l2[0]->rx_avail;
		return l2;
	}

	l2->rx_avail = CreateEvent(NULL, TRUE, FALSE, NULL);
	if (l2->rx_avail == NULL) {
		os_free(l2);
		return NULL;
	}

	eloop_register_event(l2->rx_avail, sizeof(l2->rx_avail),
			     l2_packet_rx_event, l2, NULL);

#ifdef _WIN32_WCE
	l2_ndisuio_global->stop_request = CreateEvent(NULL, TRUE, FALSE, NULL);
	/*
	 * This event is being set based on media connect/disconnect
	 * notifications in driver_ndis.c.
	 */
	l2_ndisuio_global->ready_for_read =
		CreateEvent(NULL, TRUE, FALSE, TEXT("WpaSupplicantConnected"));
	l2_ndisuio_global->rx_processed = CreateEvent(NULL, TRUE, FALSE, NULL);
	if (l2_ndisuio_global->stop_request == NULL ||
	    l2_ndisuio_global->ready_for_read == NULL ||
	    l2_ndisuio_global->rx_processed == NULL) {
		if (l2_ndisuio_global->stop_request) {
			CloseHandle(l2_ndisuio_global->stop_request);
			l2_ndisuio_global->stop_request = NULL;
		}
		if (l2_ndisuio_global->ready_for_read) {
			CloseHandle(l2_ndisuio_global->ready_for_read);
			l2_ndisuio_global->ready_for_read = NULL;
		}
		if (l2_ndisuio_global->rx_processed) {
			CloseHandle(l2_ndisuio_global->rx_processed);
			l2_ndisuio_global->rx_processed = NULL;
		}
		eloop_unregister_event(l2->rx_avail, sizeof(l2->rx_avail));
		os_free(l2);
		return NULL;
	}

	l2_ndisuio_global->rx_thread = CreateThread(NULL, 0,
						    l2_packet_rx_thread, l2, 0,
						    NULL);
	if (l2_ndisuio_global->rx_thread == NULL) {
		wpa_printf(MSG_INFO, "L2(NDISUIO): Failed to create RX "
			   "thread: %d", (int) GetLastError());
		eloop_unregister_event(l2->rx_avail, sizeof(l2->rx_avail));
		CloseHandle(l2_ndisuio_global->stop_request);
		l2_ndisuio_global->stop_request = NULL;
		os_free(l2);
		return NULL;
	}
#else /* _WIN32_WCE */
	l2_ndisuio_start_read(l2, 0);
#endif /* _WIN32_WCE */

	return l2;
}