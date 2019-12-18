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
struct l2_packet_data {char* ifname; void (* rx_callback ) (void*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,size_t) ;int l2_hdr; int /*<<< orphan*/  own_addr; void* rx_callback_ctx; } ;

/* Variables and functions */
 scalar_t__ eth_get (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ l2_packet_init_libpcap (struct l2_packet_data*,unsigned short) ; 
 int /*<<< orphan*/  os_free (struct l2_packet_data*) ; 
 int /*<<< orphan*/  os_strlcpy (char*,char const*,int) ; 
 struct l2_packet_data* os_zalloc (int) ; 
 int /*<<< orphan*/  stderr ; 

struct l2_packet_data * l2_packet_init(
	const char *ifname, const u8 *own_addr, unsigned short protocol,
	void (*rx_callback)(void *ctx, const u8 *src_addr,
			    const u8 *buf, size_t len),
	void *rx_callback_ctx, int l2_hdr)
{
	struct l2_packet_data *l2;

	l2 = os_zalloc(sizeof(struct l2_packet_data));
	if (l2 == NULL)
		return NULL;
	os_strlcpy(l2->ifname, ifname, sizeof(l2->ifname));
	l2->rx_callback = rx_callback;
	l2->rx_callback_ctx = rx_callback_ctx;
	l2->l2_hdr = l2_hdr;

	if (eth_get(l2->ifname, l2->own_addr) < 0) {
		fprintf(stderr, "Failed to get link-level address for "
			"interface '%s'.\n", l2->ifname);
		os_free(l2);
		return NULL;
	}

	if (l2_packet_init_libpcap(l2, protocol)) {
		os_free(l2);
		return NULL;
	}

	return l2;
}