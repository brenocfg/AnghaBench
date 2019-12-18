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
struct wpabuf {int dummy; } ;
struct ieee802_1x_mka_participant {void* active; struct ieee802_1x_kay* kay; } ;
struct ieee802_1x_kay {void* active; int /*<<< orphan*/  l2_mka; int /*<<< orphan*/  if_name; } ;
struct ieee802_1x_hdr {int dummy; } ;
struct ieee8023_hdr {int dummy; } ;
struct TYPE_3__ {scalar_t__ (* body_length ) (struct ieee802_1x_mka_participant*) ;scalar_t__ (* body_present ) (struct ieee802_1x_mka_participant*) ;} ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 int /*<<< orphan*/  MSG_MSGDUMP ; 
 void* TRUE ; 
 scalar_t__ ieee802_1x_kay_encode_mkpdu (struct ieee802_1x_mka_participant*,struct wpabuf*) ; 
 int /*<<< orphan*/  l2_packet_send (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* mka_body_handler ; 
 scalar_t__ stub1 (struct ieee802_1x_mka_participant*) ; 
 scalar_t__ stub2 (struct ieee802_1x_mka_participant*) ; 
 int /*<<< orphan*/  wpa_hexdump_buf (int /*<<< orphan*/ ,char*,struct wpabuf*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 struct wpabuf* wpabuf_alloc (size_t) ; 
 int /*<<< orphan*/  wpabuf_free (struct wpabuf*) ; 
 int /*<<< orphan*/  wpabuf_head (struct wpabuf*) ; 
 int /*<<< orphan*/  wpabuf_len (struct wpabuf*) ; 

__attribute__((used)) static int
ieee802_1x_participant_send_mkpdu(
	struct ieee802_1x_mka_participant *participant)
{
	struct wpabuf *buf;
	struct ieee802_1x_kay *kay = participant->kay;
	size_t length = 0;
	unsigned int i;

	wpa_printf(MSG_DEBUG, "KaY: Encode and send an MKPDU (ifname=%s)",
		   kay->if_name);
	length += sizeof(struct ieee802_1x_hdr) + sizeof(struct ieee8023_hdr);
	for (i = 0; i < ARRAY_SIZE(mka_body_handler); i++) {
		if (mka_body_handler[i].body_present &&
		    mka_body_handler[i].body_present(participant))
			length += mka_body_handler[i].body_length(participant);
	}

	buf = wpabuf_alloc(length);
	if (!buf) {
		wpa_printf(MSG_ERROR, "KaY: out of memory");
		return -1;
	}

	if (ieee802_1x_kay_encode_mkpdu(participant, buf)) {
		wpa_printf(MSG_ERROR, "KaY: encode mkpdu fail");
		return -1;
	}

	wpa_hexdump_buf(MSG_MSGDUMP, "KaY: Outgoing MKPDU", buf);
	l2_packet_send(kay->l2_mka, NULL, 0, wpabuf_head(buf), wpabuf_len(buf));
	wpabuf_free(buf);

	kay->active = TRUE;
	participant->active = TRUE;

	return 0;
}