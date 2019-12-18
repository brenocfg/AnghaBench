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
struct nlattr {int dummy; } ;
struct hostapd_hw_modes {int /*<<< orphan*/ * he_capab; } ;

/* Variables and functions */
 unsigned int IEEE80211_MODE_NUM ; 
 size_t NL80211_BAND_IFTYPE_ATTR_IFTYPES ; 
 int /*<<< orphan*/  NL80211_BAND_IFTYPE_ATTR_MAX ; 
 int /*<<< orphan*/  NL80211_IFTYPE_MAX ; 
 int NL_OK ; 
 int NL_STOP ; 
 int /*<<< orphan*/  nla_data (struct nlattr*) ; 
 int /*<<< orphan*/  nla_len (struct nlattr*) ; 
 int /*<<< orphan*/  nla_parse (struct nlattr**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ nla_parse_nested (struct nlattr**,int /*<<< orphan*/ ,struct nlattr*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  phy_info_iftype_copy (int /*<<< orphan*/ *,unsigned int,struct nlattr**,struct nlattr**) ; 

__attribute__((used)) static int phy_info_iftype(struct hostapd_hw_modes *mode,
			   struct nlattr *nl_iftype)
{
	struct nlattr *tb[NL80211_BAND_IFTYPE_ATTR_MAX + 1];
	struct nlattr *tb_flags[NL80211_IFTYPE_MAX + 1];
	unsigned int i;

	nla_parse(tb, NL80211_BAND_IFTYPE_ATTR_MAX,
		  nla_data(nl_iftype), nla_len(nl_iftype), NULL);

	if (!tb[NL80211_BAND_IFTYPE_ATTR_IFTYPES])
		return NL_STOP;

	if (nla_parse_nested(tb_flags, NL80211_IFTYPE_MAX,
			     tb[NL80211_BAND_IFTYPE_ATTR_IFTYPES], NULL))
		return NL_STOP;

	for (i = 0; i < IEEE80211_MODE_NUM; i++)
		phy_info_iftype_copy(&mode->he_capab[i], i, tb, tb_flags);

	return NL_OK;
}