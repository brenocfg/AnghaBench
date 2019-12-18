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
struct mbuf {int dummy; } ;
struct ieee80211_node {int dummy; } ;
struct ieee80211_bpf_params {scalar_t__ ibp_rate0; scalar_t__ ibp_rate1; scalar_t__ ibp_rate2; scalar_t__ ibp_rate3; } ;

/* Variables and functions */
 int ieee80211_validate_rate (struct ieee80211_node*,scalar_t__) ; 

__attribute__((used)) static int
ieee80211_sanitize_rates(struct ieee80211_node *ni, struct mbuf *m,
    const struct ieee80211_bpf_params *params)
{
	int error;

	if (!params)
		return (0);	/* nothing to do */

	/* NB: most drivers assume that ibp_rate0 is set (!= 0). */
	if (params->ibp_rate0 != 0) {
		error = ieee80211_validate_rate(ni, params->ibp_rate0);
		if (error != 0)
			return (error);
	} else {
		/* XXX pre-setup some default (e.g., mgmt / mcast) rate */
		/* XXX __DECONST? */
		(void) m;
	}

	if (params->ibp_rate1 != 0 &&
	    (error = ieee80211_validate_rate(ni, params->ibp_rate1)) != 0)
		return (error);

	if (params->ibp_rate2 != 0 &&
	    (error = ieee80211_validate_rate(ni, params->ibp_rate2)) != 0)
		return (error);

	if (params->ibp_rate3 != 0 &&
	    (error = ieee80211_validate_rate(ni, params->ibp_rate3)) != 0)
		return (error);

	return (0);
}