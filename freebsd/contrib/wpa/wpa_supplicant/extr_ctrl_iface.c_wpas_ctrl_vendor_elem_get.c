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
struct wpa_supplicant {int /*<<< orphan*/ ** vendor_elem; } ;

/* Variables and functions */
 int NUM_VENDOR_ELEM_FRAMES ; 
 int atoi (char*) ; 
 int wpa_snprintf_hex (char*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpabuf_head_u8 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpabuf_len (int /*<<< orphan*/ *) ; 
 struct wpa_supplicant* wpas_vendor_elem (struct wpa_supplicant*,int) ; 

__attribute__((used)) static int wpas_ctrl_vendor_elem_get(struct wpa_supplicant *wpa_s, char *cmd,
				     char *buf, size_t buflen)
{
	int frame = atoi(cmd);

	if (frame < 0 || frame >= NUM_VENDOR_ELEM_FRAMES)
		return -1;
	wpa_s = wpas_vendor_elem(wpa_s, frame);

	if (wpa_s->vendor_elem[frame] == NULL)
		return 0;

	return wpa_snprintf_hex(buf, buflen,
				wpabuf_head_u8(wpa_s->vendor_elem[frame]),
				wpabuf_len(wpa_s->vendor_elem[frame]));
}