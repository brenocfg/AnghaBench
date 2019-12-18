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
struct wpa_supplicant {TYPE_1__* non_pref_chan; } ;
struct TYPE_2__ {int /*<<< orphan*/  reason; int /*<<< orphan*/  preference; int /*<<< orphan*/  chan; int /*<<< orphan*/  oper_class; } ;

/* Variables and functions */
 int /*<<< orphan*/  wpabuf_put_u8 (struct wpabuf*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wpas_mbo_non_pref_chan_attr_body(struct wpa_supplicant *wpa_s,
					     struct wpabuf *mbo,
					     u8 start, u8 end)
{
	u8 i;

	wpabuf_put_u8(mbo, wpa_s->non_pref_chan[start].oper_class);

	for (i = start; i < end; i++)
		wpabuf_put_u8(mbo, wpa_s->non_pref_chan[i].chan);

	wpabuf_put_u8(mbo, wpa_s->non_pref_chan[start].preference);
	wpabuf_put_u8(mbo, wpa_s->non_pref_chan[start].reason);
}