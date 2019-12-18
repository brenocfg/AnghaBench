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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u16 ;
struct wpa_supplicant {TYPE_1__* conf; } ;
struct ieee802_1x_hdr {int /*<<< orphan*/  length; int /*<<< orphan*/  type; int /*<<< orphan*/  version; } ;
struct TYPE_2__ {int /*<<< orphan*/  eapol_version; } ;

/* Variables and functions */
 int /*<<< orphan*/  host_to_be16 (int) ; 
 struct ieee802_1x_hdr* os_malloc (size_t) ; 
 int /*<<< orphan*/  os_memcpy (struct ieee802_1x_hdr*,void const*,int) ; 
 int /*<<< orphan*/  os_memset (struct ieee802_1x_hdr*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static u8 * wpa_alloc_eapol(const struct wpa_supplicant *wpa_s, u8 type,
			    const void *data, u16 data_len,
			    size_t *msg_len, void **data_pos)
{
	struct ieee802_1x_hdr *hdr;

	*msg_len = sizeof(*hdr) + data_len;
	hdr = os_malloc(*msg_len);
	if (hdr == NULL)
		return NULL;

	hdr->version = wpa_s->conf->eapol_version;
	hdr->type = type;
	hdr->length = host_to_be16(data_len);

	if (data)
		os_memcpy(hdr + 1, data, data_len);
	else
		os_memset(hdr + 1, 0, data_len);

	if (data_pos)
		*data_pos = hdr + 1;

	return (u8 *) hdr;
}