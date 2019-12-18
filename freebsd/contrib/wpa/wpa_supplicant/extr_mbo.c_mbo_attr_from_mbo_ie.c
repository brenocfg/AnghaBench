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
typedef  int u8 ;
typedef  enum mbo_attr_id { ____Placeholder_mbo_attr_id } mbo_attr_id ;

/* Variables and functions */
 int MBO_IE_HEADER ; 
 int const* get_ie (int const*,int,int) ; 

const u8 * mbo_attr_from_mbo_ie(const u8 *mbo_ie, enum mbo_attr_id attr)
{
	const u8 *mbo;
	u8 ie_len = mbo_ie[1];

	if (ie_len < MBO_IE_HEADER - 2)
		return NULL;
	mbo = mbo_ie + MBO_IE_HEADER;

	return get_ie(mbo, 2 + ie_len - MBO_IE_HEADER, attr);
}