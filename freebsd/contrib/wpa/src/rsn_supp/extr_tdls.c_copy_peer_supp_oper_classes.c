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
struct wpa_tdls_peer {scalar_t__ supp_oper_classes_len; int /*<<< orphan*/ * supp_oper_classes; } ;
struct wpa_eapol_ie_parse {scalar_t__ supp_oper_classes_len; int /*<<< orphan*/  supp_oper_classes; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  os_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/ * os_zalloc (scalar_t__) ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int copy_peer_supp_oper_classes(const struct wpa_eapol_ie_parse *kde,
				       struct wpa_tdls_peer *peer)
{
	if (!kde->supp_oper_classes) {
		wpa_printf(MSG_DEBUG, "TDLS: No supported operating classes received");
		return 0;
	}

	if (!peer->supp_oper_classes ||
	    peer->supp_oper_classes_len < kde->supp_oper_classes_len) {
		os_free(peer->supp_oper_classes);
		peer->supp_oper_classes = os_zalloc(kde->supp_oper_classes_len);
		if (peer->supp_oper_classes == NULL)
			return -1;
	}

	peer->supp_oper_classes_len = kde->supp_oper_classes_len;
	os_memcpy(peer->supp_oper_classes, kde->supp_oper_classes,
		  peer->supp_oper_classes_len);
	wpa_hexdump(MSG_DEBUG, "TDLS: Peer Supported Operating Classes",
		    (u8 *) peer->supp_oper_classes,
		    peer->supp_oper_classes_len);
	return 0;
}