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
struct ieee802_1x_mka_hdr {unsigned int length; unsigned int length1; } ;

/* Variables and functions */

__attribute__((used)) static void set_mka_param_body_len(void *body, unsigned int len)
{
	struct ieee802_1x_mka_hdr *hdr = body;
	hdr->length = (len >> 8) & 0x0f;
	hdr->length1 = len & 0xff;
}