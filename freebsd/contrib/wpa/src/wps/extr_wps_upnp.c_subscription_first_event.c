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
typedef  int /*<<< orphan*/  txt ;
struct wpabuf {int dummy; } ;
struct subscription {TYPE_1__* sm; } ;
struct TYPE_2__ {char* wlanevent; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 scalar_t__ base64_encode (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct wpabuf* build_fake_wsc_ack () ; 
 int event_add (struct subscription*,struct wpabuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_snprintf (char*,int,char*,int) ; 
 scalar_t__ os_strlen (char*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 struct wpabuf* wpabuf_alloc (scalar_t__) ; 
 int /*<<< orphan*/  wpabuf_free (struct wpabuf*) ; 
 int /*<<< orphan*/  wpabuf_head (struct wpabuf*) ; 
 int /*<<< orphan*/  wpabuf_len (struct wpabuf*) ; 
 int /*<<< orphan*/  wpabuf_put_property (struct wpabuf*,char*,char*) ; 
 int /*<<< orphan*/  wpabuf_put_str (struct wpabuf*,char const*) ; 

__attribute__((used)) static int subscription_first_event(struct subscription *s)
{
	/*
	 * Actually, utf-8 is the default, but it doesn't hurt to specify it.
	 *
	 * APStatus is apparently a bit set,
	 * 0x1 = configuration change (but is always set?)
	 * 0x10 = ap is locked
	 *
	 * Per UPnP spec, we send out the last value of each variable, even
	 * for WLANEvent, whatever it was.
	 */
	char *wlan_event;
	struct wpabuf *buf;
	int ap_status = 1;      /* TODO: add 0x10 if access point is locked */
	const char *head =
		"<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
		"<e:propertyset xmlns:e=\"urn:schemas-upnp-org:event-1-0\">\n";
	const char *tail = "</e:propertyset>\n";
	char txt[10];
	int ret;

	if (s->sm->wlanevent == NULL) {
		/*
		 * There has been no events before the subscription. However,
		 * UPnP device architecture specification requires all the
		 * evented variables to be included, so generate a dummy event
		 * for this particular case using a WSC_ACK and all-zeros
		 * nonces. The ER (UPnP control point) will ignore this, but at
		 * least it will learn that WLANEvent variable will be used in
		 * event notifications in the future.
		 */
		struct wpabuf *msg;
		wpa_printf(MSG_DEBUG, "WPS UPnP: Use a fake WSC_ACK as the "
			   "initial WLANEvent");
		msg = build_fake_wsc_ack();
		if (msg) {
			s->sm->wlanevent = (char *)
				base64_encode(wpabuf_head(msg),
					      wpabuf_len(msg), NULL);
			wpabuf_free(msg);
		}
	}

	wlan_event = s->sm->wlanevent;
	if (wlan_event == NULL || *wlan_event == '\0') {
		wpa_printf(MSG_DEBUG, "WPS UPnP: WLANEvent not known for "
			   "initial event message");
		wlan_event = "";
	}
	buf = wpabuf_alloc(500 + os_strlen(wlan_event));
	if (buf == NULL)
		return -1;

	wpabuf_put_str(buf, head);
	wpabuf_put_property(buf, "STAStatus", "1");
	os_snprintf(txt, sizeof(txt), "%d", ap_status);
	wpabuf_put_property(buf, "APStatus", txt);
	if (*wlan_event)
		wpabuf_put_property(buf, "WLANEvent", wlan_event);
	wpabuf_put_str(buf, tail);

	ret = event_add(s, buf, 0);
	if (ret) {
		wpabuf_free(buf);
		return ret;
	}
	wpabuf_free(buf);

	return 0;
}