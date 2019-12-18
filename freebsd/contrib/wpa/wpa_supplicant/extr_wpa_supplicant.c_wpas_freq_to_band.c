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
typedef  enum wpa_radio_work_band { ____Placeholder_wpa_radio_work_band } wpa_radio_work_band ;

/* Variables and functions */
 int BAND_2_4_GHZ ; 
 int BAND_5_GHZ ; 
 int BAND_60_GHZ ; 

enum wpa_radio_work_band wpas_freq_to_band(int freq)
{
	if (freq < 3000)
		return BAND_2_4_GHZ;
	if (freq > 50000)
		return BAND_60_GHZ;
	return BAND_5_GHZ;
}