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
struct wpabuf {int dummy; } ;
struct p2p_reg_class {int reg_class; int channels; char const* channel; } ;
struct p2p_channels {size_t reg_classes; struct p2p_reg_class* reg_class; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int P2P_ATTR_CHANNEL_LIST ; 
 int /*<<< orphan*/  WPA_PUT_LE16 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * wpabuf_put (struct wpabuf*,int) ; 
 int /*<<< orphan*/  wpabuf_put_data (struct wpabuf*,char const*,int) ; 
 int /*<<< orphan*/  wpabuf_put_u8 (struct wpabuf*,int) ; 

void p2p_buf_add_channel_list(struct wpabuf *buf, const char *country,
			      struct p2p_channels *chan)
{
	u8 *len;
	size_t i;

	/* Channel List */
	wpabuf_put_u8(buf, P2P_ATTR_CHANNEL_LIST);
	len = wpabuf_put(buf, 2); /* IE length to be filled */
	wpabuf_put_data(buf, country, 3); /* Country String */

	for (i = 0; i < chan->reg_classes; i++) {
		struct p2p_reg_class *c = &chan->reg_class[i];
		wpabuf_put_u8(buf, c->reg_class);
		wpabuf_put_u8(buf, c->channels);
		wpabuf_put_data(buf, c->channel, c->channels);
	}

	/* Update attribute length */
	WPA_PUT_LE16(len, (u8 *) wpabuf_put(buf, 0) - len - 2);
	wpa_hexdump(MSG_DEBUG, "P2P: * Channel List",
		    len + 2, (u8 *) wpabuf_put(buf, 0) - len - 2);
}