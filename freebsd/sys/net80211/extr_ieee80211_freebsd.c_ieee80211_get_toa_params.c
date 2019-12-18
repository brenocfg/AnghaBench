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
struct m_tag {int dummy; } ;
struct ieee80211_toa_params {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MTAG_ABI_NET80211 ; 
 int /*<<< orphan*/  NET80211_TAG_TOA_PARAMS ; 
 struct m_tag* m_tag_locate (struct mbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (struct ieee80211_toa_params*,struct ieee80211_toa_params*,int) ; 

int
ieee80211_get_toa_params(struct mbuf *m, struct ieee80211_toa_params *p)
{
	struct m_tag *mtag;
	struct ieee80211_toa_params *rp;

	mtag = m_tag_locate(m, MTAG_ABI_NET80211, NET80211_TAG_TOA_PARAMS,
	    NULL);
	if (mtag == NULL)
		return (0);
	rp = (struct ieee80211_toa_params *)(mtag + 1);
	if (p != NULL)
		memcpy(p, rp, sizeof(*p));
	return (1);
}