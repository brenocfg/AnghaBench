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
struct wpabuf {int dummy; } ;

/* Variables and functions */
 size_t MBO_ATTR_ID_NON_PREF_CHAN_REPORT ; 
 int /*<<< orphan*/  wpabuf_put_u8 (struct wpabuf*,size_t) ; 

__attribute__((used)) static void wpas_mbo_non_pref_chan_attr_hdr(struct wpabuf *mbo, size_t size)
{
	wpabuf_put_u8(mbo, MBO_ATTR_ID_NON_PREF_CHAN_REPORT);
	wpabuf_put_u8(mbo, size); /* Length */
}