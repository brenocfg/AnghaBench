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
typedef  int /*<<< orphan*/  u8 ;
struct fst_iface {int dummy; } ;
typedef  enum mb_band_id { ____Placeholder_mb_band_id } mb_band_id ;
typedef  enum hostapd_hw_mode { ____Placeholder_hostapd_hw_mode } hostapd_hw_mode ;

/* Variables and functions */
 int fst_hw_mode_to_band (int) ; 
 int /*<<< orphan*/  fst_iface_get_channel_info (struct fst_iface*,int*,int /*<<< orphan*/ *) ; 

enum mb_band_id fst_iface_get_band_id(struct fst_iface *i)
{
	enum hostapd_hw_mode hw_mode;
	u8 channel;

	fst_iface_get_channel_info(i, &hw_mode, &channel);
	return fst_hw_mode_to_band(hw_mode);
}