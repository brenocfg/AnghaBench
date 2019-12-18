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
struct mb_ies_info {size_t nof_ies; TYPE_1__* ies; } ;
struct TYPE_2__ {scalar_t__ ie_len; int /*<<< orphan*/  ie; } ;

/* Variables and functions */
 scalar_t__ WLAN_EID_MULTI_BAND ; 
 int /*<<< orphan*/  WPA_ASSERT (int /*<<< orphan*/ ) ; 
 struct wpabuf* wpabuf_alloc (size_t) ; 
 int /*<<< orphan*/  wpabuf_put_data (struct wpabuf*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  wpabuf_put_u8 (struct wpabuf*,scalar_t__) ; 

struct wpabuf * mb_ies_by_info(struct mb_ies_info *info)
{
	struct wpabuf *mb_ies = NULL;

	WPA_ASSERT(info != NULL);

	if (info->nof_ies) {
		u8 i;
		size_t mb_ies_size = 0;

		for (i = 0; i < info->nof_ies; i++)
			mb_ies_size += 2 + info->ies[i].ie_len;

		mb_ies = wpabuf_alloc(mb_ies_size);
		if (mb_ies) {
			for (i = 0; i < info->nof_ies; i++) {
				wpabuf_put_u8(mb_ies, WLAN_EID_MULTI_BAND);
				wpabuf_put_u8(mb_ies, info->ies[i].ie_len);
				wpabuf_put_data(mb_ies,
						info->ies[i].ie,
						info->ies[i].ie_len);
			}
		}
	}

	return mb_ies;
}