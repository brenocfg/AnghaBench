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
typedef  size_t u8 ;
struct wpabuf {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  new_peer_addr; int /*<<< orphan*/  old_peer_addr; struct fst_iface* new_iface; struct fst_iface* old_iface; } ;
struct fst_session {TYPE_1__ data; } ;
struct fst_iface {int dummy; } ;
typedef  scalar_t__ Boolean ;

/* Variables and functions */
 size_t FST_ACTION_MAX_SUPPORTED ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 int /*<<< orphan*/  WLAN_ACTION_FST ; 
 int /*<<< orphan*/  WPA_ASSERT (int) ; 
 int /*<<< orphan*/ * fst_action_names ; 
 int fst_iface_send_action (struct fst_iface*,int /*<<< orphan*/ ,struct wpabuf*) ; 
 int /*<<< orphan*/  fst_printf_session (struct fst_session*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  fst_printf_siface (struct fst_session*,struct fst_iface*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 struct wpabuf* wpabuf_alloc (size_t) ; 
 int /*<<< orphan*/  wpabuf_free (struct wpabuf*) ; 
 int /*<<< orphan*/  wpabuf_put_buf (struct wpabuf*,struct wpabuf const*) ; 
 int /*<<< orphan*/  wpabuf_put_data (struct wpabuf*,void const*,size_t) ; 
 int /*<<< orphan*/  wpabuf_put_u8 (struct wpabuf*,int /*<<< orphan*/ ) ; 
 scalar_t__ wpabuf_size (struct wpabuf const*) ; 

__attribute__((used)) static int fst_session_send_action(struct fst_session *s, Boolean old_iface,
				   const void *payload, size_t size,
				   const struct wpabuf *extra_buf)
{
	size_t len;
	int res;
	struct wpabuf *buf;
	u8 action;
	struct fst_iface *iface =
		old_iface ? s->data.old_iface : s->data.new_iface;

	WPA_ASSERT(payload != NULL);
	WPA_ASSERT(size != 0);

	action = *(const u8 *) payload;

	WPA_ASSERT(action <= FST_ACTION_MAX_SUPPORTED);

	if (!iface) {
		fst_printf_session(s, MSG_ERROR,
				   "no %s interface for FST Action '%s' sending",
				   old_iface ? "old" : "new",
				   fst_action_names[action]);
		return -1;
	}

	len = sizeof(u8) /* category */ + size;
	if (extra_buf)
		len += wpabuf_size(extra_buf);

	buf = wpabuf_alloc(len);
	if (!buf) {
		fst_printf_session(s, MSG_ERROR,
				   "cannot allocate buffer of %zu bytes for FST Action '%s' sending",
				   len, fst_action_names[action]);
		return -1;
	}

	wpabuf_put_u8(buf, WLAN_ACTION_FST);
	wpabuf_put_data(buf, payload, size);
	if (extra_buf)
		wpabuf_put_buf(buf, extra_buf);

	res = fst_iface_send_action(iface,
				    old_iface ? s->data.old_peer_addr :
				    s->data.new_peer_addr, buf);
	if (res < 0)
		fst_printf_siface(s, iface, MSG_ERROR,
				  "failed to send FST Action '%s'",
				  fst_action_names[action]);
	else
		fst_printf_siface(s, iface, MSG_DEBUG, "FST Action '%s' sent",
				  fst_action_names[action]);
	wpabuf_free(buf);

	return res;
}