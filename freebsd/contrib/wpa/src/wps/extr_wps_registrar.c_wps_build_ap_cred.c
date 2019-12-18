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
struct wps_data {int dummy; } ;
struct wpabuf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATTR_CRED ; 
 struct wpabuf* wpabuf_alloc (int) ; 
 int /*<<< orphan*/  wpabuf_clear_free (struct wpabuf*) ; 
 int /*<<< orphan*/  wpabuf_free (struct wpabuf*) ; 
 int /*<<< orphan*/  wpabuf_len (struct wpabuf*) ; 
 int /*<<< orphan*/  wpabuf_put_be16 (struct wpabuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpabuf_put_buf (struct wpabuf*,struct wpabuf*) ; 
 scalar_t__ wps_build_ap_settings (struct wps_data*,struct wpabuf*) ; 

__attribute__((used)) static struct wpabuf * wps_build_ap_cred(struct wps_data *wps)
{
	struct wpabuf *msg, *plain;

	msg = wpabuf_alloc(1000);
	if (msg == NULL)
		return NULL;

	plain = wpabuf_alloc(200);
	if (plain == NULL) {
		wpabuf_free(msg);
		return NULL;
	}

	if (wps_build_ap_settings(wps, plain)) {
		wpabuf_clear_free(plain);
		wpabuf_free(msg);
		return NULL;
	}

	wpabuf_put_be16(msg, ATTR_CRED);
	wpabuf_put_be16(msg, wpabuf_len(plain));
	wpabuf_put_buf(msg, plain);
	wpabuf_clear_free(plain);

	return msg;
}