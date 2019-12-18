#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  modes; } ;
struct wpa_supplicant {TYPE_1__ hw; } ;
struct ubus_request_data {int dummy; } ;
struct ubus_object {int dummy; } ;
struct ubus_context {int dummy; } ;
struct blob_attr {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  head; } ;

/* Variables and functions */
 TYPE_2__ b ; 
 int /*<<< orphan*/  blob_buf_init (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blobmsg_add_u8 (TYPE_2__*,char*,int /*<<< orphan*/ ) ; 
 struct wpa_supplicant* get_wpas_from_object (struct ubus_object*) ; 
 int /*<<< orphan*/  ht_supported (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ubus_send_reply (struct ubus_context*,struct ubus_request_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vht_supported (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
wpas_bss_get_features(struct ubus_context *ctx, struct ubus_object *obj,
			struct ubus_request_data *req, const char *method,
			struct blob_attr *msg)
{
	struct wpa_supplicant *wpa_s = get_wpas_from_object(obj);

	blob_buf_init(&b, 0);
	blobmsg_add_u8(&b, "ht_supported", ht_supported(wpa_s->hw.modes));
	blobmsg_add_u8(&b, "vht_supported", vht_supported(wpa_s->hw.modes));
	ubus_send_reply(ctx, req, b.head);

	return 0;
}