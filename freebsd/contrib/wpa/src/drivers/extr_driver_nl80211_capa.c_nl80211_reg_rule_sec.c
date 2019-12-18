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
typedef  int u32 ;
typedef  size_t u16 ;
struct phy_info_arg {size_t* num_modes; TYPE_1__* modes; } ;
struct nlattr {int dummy; } ;
struct TYPE_2__ {int ht_capab; } ;

/* Variables and functions */
 int HT_CAP_INFO_SUPP_CHANNEL_WIDTH_SET ; 
 size_t NL80211_ATTR_FREQ_RANGE_END ; 
 size_t NL80211_ATTR_FREQ_RANGE_MAX_BW ; 
 size_t NL80211_ATTR_FREQ_RANGE_START ; 
 int /*<<< orphan*/  nl80211_set_ht40_mode_sec (TYPE_1__*,int,int) ; 
 int nla_get_u32 (struct nlattr*) ; 

__attribute__((used)) static void nl80211_reg_rule_sec(struct nlattr *tb[],
				 struct phy_info_arg *results)
{
	u32 start, end, max_bw;
	u16 m;

	if (tb[NL80211_ATTR_FREQ_RANGE_START] == NULL ||
	    tb[NL80211_ATTR_FREQ_RANGE_END] == NULL ||
	    tb[NL80211_ATTR_FREQ_RANGE_MAX_BW] == NULL)
		return;

	start = nla_get_u32(tb[NL80211_ATTR_FREQ_RANGE_START]) / 1000;
	end = nla_get_u32(tb[NL80211_ATTR_FREQ_RANGE_END]) / 1000;
	max_bw = nla_get_u32(tb[NL80211_ATTR_FREQ_RANGE_MAX_BW]) / 1000;

	if (max_bw < 20)
		return;

	for (m = 0; m < *results->num_modes; m++) {
		if (!(results->modes[m].ht_capab &
		      HT_CAP_INFO_SUPP_CHANNEL_WIDTH_SET))
			continue;
		nl80211_set_ht40_mode_sec(&results->modes[m], start, end);
	}
}