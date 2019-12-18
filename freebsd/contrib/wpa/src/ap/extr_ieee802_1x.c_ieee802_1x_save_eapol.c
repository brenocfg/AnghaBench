#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct sta_info {TYPE_1__* pending_eapol_rx; } ;
struct TYPE_3__ {int /*<<< orphan*/  rx_time; int /*<<< orphan*/  buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  os_free (TYPE_1__*) ; 
 int /*<<< orphan*/  os_get_reltime (int /*<<< orphan*/ *) ; 
 TYPE_1__* os_malloc (int) ; 
 int /*<<< orphan*/  wpabuf_alloc_copy (int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  wpabuf_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ieee802_1x_save_eapol(struct sta_info *sta, const u8 *buf,
				  size_t len)
{
	if (sta->pending_eapol_rx) {
		wpabuf_free(sta->pending_eapol_rx->buf);
	} else {
		sta->pending_eapol_rx =
			os_malloc(sizeof(*sta->pending_eapol_rx));
		if (!sta->pending_eapol_rx)
			return;
	}

	sta->pending_eapol_rx->buf = wpabuf_alloc_copy(buf, len);
	if (!sta->pending_eapol_rx->buf) {
		os_free(sta->pending_eapol_rx);
		sta->pending_eapol_rx = NULL;
		return;
	}

	os_get_reltime(&sta->pending_eapol_rx->rx_time);
}