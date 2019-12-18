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
typedef  struct l2_ethhdr {int /*<<< orphan*/  h_proto; struct l2_ethhdr const* h_source; struct l2_ethhdr const* h_dest; } const l2_ethhdr ;
typedef  struct l2_ethhdr u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct l2_packet_data {struct l2_ethhdr const* own_addr; scalar_t__ l2_hdr; } ;
typedef  int /*<<< orphan*/  overlapped ;
typedef  int /*<<< orphan*/  OVERLAPPED ;
typedef  scalar_t__ DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ ERROR_IO_PENDING ; 
 size_t ETH_ALEN ; 
 scalar_t__ GetLastError () ; 
 scalar_t__ GetOverlappedResult (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ WriteFile (int /*<<< orphan*/ ,struct l2_ethhdr const*,size_t,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  driver_ndis_get_ndisuio_handle () ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_free (struct l2_ethhdr const*) ; 
 struct l2_ethhdr* os_malloc (size_t) ; 
 int /*<<< orphan*/  os_memcpy (struct l2_ethhdr const*,struct l2_ethhdr const*,size_t) ; 
 int /*<<< orphan*/  os_memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

int l2_packet_send(struct l2_packet_data *l2, const u8 *dst_addr, u16 proto,
		   const u8 *buf, size_t len)
{
	BOOL res;
	DWORD written;
	struct l2_ethhdr *eth;
#ifndef _WIN32_WCE
	OVERLAPPED overlapped;
#endif /* _WIN32_WCE */
	OVERLAPPED *o;

	if (l2 == NULL)
		return -1;

#ifdef _WIN32_WCE
	o = NULL;
#else /* _WIN32_WCE */
	os_memset(&overlapped, 0, sizeof(overlapped));
	o = &overlapped;
#endif /* _WIN32_WCE */

	if (l2->l2_hdr) {
		res = WriteFile(driver_ndis_get_ndisuio_handle(), buf, len,
				&written, o);
	} else {
		size_t mlen = sizeof(*eth) + len;
		eth = os_malloc(mlen);
		if (eth == NULL)
			return -1;

		os_memcpy(eth->h_dest, dst_addr, ETH_ALEN);
		os_memcpy(eth->h_source, l2->own_addr, ETH_ALEN);
		eth->h_proto = htons(proto);
		os_memcpy(eth + 1, buf, len);
		res = WriteFile(driver_ndis_get_ndisuio_handle(), eth, mlen,
				&written, o);
		os_free(eth);
	}

	if (!res) {
		DWORD err = GetLastError();
#ifndef _WIN32_WCE
		if (err == ERROR_IO_PENDING) {
			wpa_printf(MSG_DEBUG, "L2(NDISUIO): Wait for pending "
				   "write to complete");
			res = GetOverlappedResult(
				driver_ndis_get_ndisuio_handle(), &overlapped,
				&written, TRUE);
			if (!res) {
				wpa_printf(MSG_DEBUG, "L2(NDISUIO): "
					   "GetOverlappedResult failed: %d",
					   (int) GetLastError());
				return -1;
			}
			return 0;
		}
#endif /* _WIN32_WCE */
		wpa_printf(MSG_DEBUG, "L2(NDISUIO): WriteFile failed: %d",
			   (int) GetLastError());
		return -1;
	}

	return 0;
}