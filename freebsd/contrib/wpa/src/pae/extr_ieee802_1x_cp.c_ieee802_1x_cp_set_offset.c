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
struct ieee802_1x_cp_sm {int cipher_offset; } ;
typedef  enum confidentiality_offset { ____Placeholder_confidentiality_offset } confidentiality_offset ;

/* Variables and functions */

void ieee802_1x_cp_set_offset(void *cp_ctx, enum confidentiality_offset offset)
{
	struct ieee802_1x_cp_sm *sm = cp_ctx;
	sm->cipher_offset = offset;
}