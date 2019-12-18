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
typedef  int uint8_t ;
struct ieee80211vap {int dummy; } ;
struct ieee80211_frame {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_DISCARD (struct ieee80211vap*,int,struct ieee80211_frame const*,int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  IEEE80211_MESHPERR_DEST_SZ ; 
 int /*<<< orphan*/  IEEE80211_MESHPERR_DEST_SZ_AE ; 
 int const IEEE80211_MESHPERR_FLAGS_AE ; 
 int IEEE80211_MESHPERR_MAXDEST ; 
 size_t IEEE80211_MESHPERR_NDEST_OFFSET ; 
 int IEEE80211_MSG_ACTION ; 
 int IEEE80211_MSG_HWMP ; 

__attribute__((used)) static int
verify_mesh_perr_len(struct ieee80211vap *vap,
    const struct ieee80211_frame *wh, const uint8_t *iefrm)
{
	int alloc_sz = -1;
	const uint8_t *iefrm_t = iefrm;
	uint8_t ndest = iefrm_t[IEEE80211_MESHPERR_NDEST_OFFSET];
	int i;

	if(ndest > IEEE80211_MESHPERR_MAXDEST) {
		IEEE80211_DISCARD(vap,
		    IEEE80211_MSG_ACTION | IEEE80211_MSG_HWMP,
		    wh, NULL, "PERR with wrong number of destionat (>19), %u",
		    ndest);
		return (-1);
	}

	iefrm_t += IEEE80211_MESHPERR_NDEST_OFFSET + 1; /* flag is next field */
	/* We need to check each destionation flag to know size */
	for(i = 0; i<ndest; i++) {
		if ((*iefrm_t) & IEEE80211_MESHPERR_FLAGS_AE)
			iefrm_t += IEEE80211_MESHPERR_DEST_SZ_AE;
		else
			iefrm_t += IEEE80211_MESHPERR_DEST_SZ;
	}

	alloc_sz = (iefrm_t - iefrm) - 2; /* action + code */
	if(alloc_sz !=  iefrm[1]) {
		IEEE80211_DISCARD(vap,
		    IEEE80211_MSG_ACTION | IEEE80211_MSG_HWMP,
		    wh, NULL, "%s", "PERR with wrong len");
		return (-1);
	}
	return ndest;
}