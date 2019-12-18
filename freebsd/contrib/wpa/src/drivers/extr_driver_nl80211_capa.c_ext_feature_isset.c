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
typedef  enum nl80211_ext_feature_index { ____Placeholder_nl80211_ext_feature_index } nl80211_ext_feature_index ;

/* Variables and functions */
 int BIT (int) ; 

__attribute__((used)) static int ext_feature_isset(const u8 *ext_features, int ext_features_len,
			     enum nl80211_ext_feature_index ftidx)
{
	u8 ft_byte;

	if ((int) ftidx / 8 >= ext_features_len)
		return 0;

	ft_byte = ext_features[ftidx / 8];
	return (ft_byte & BIT(ftidx % 8)) != 0;
}