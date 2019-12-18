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
typedef  int uint32_t ;
typedef  scalar_t__ uint16_t ;
struct ifmedia_entry {int ifm_media; } ;

/* Variables and functions */
 int IEEE80211_F_TURBOP ; 
 scalar_t__ IEEE80211_MODE_11A ; 
 scalar_t__ IEEE80211_MODE_11B ; 
 scalar_t__ IEEE80211_MODE_11G ; 
 scalar_t__ IEEE80211_MODE_11NA ; 
 scalar_t__ IEEE80211_MODE_11NG ; 
 scalar_t__ IEEE80211_MODE_AUTO ; 
 scalar_t__ IEEE80211_MODE_FH ; 
 scalar_t__ IEEE80211_MODE_STURBO_A ; 
 scalar_t__ IEEE80211_MODE_TURBO_A ; 
 scalar_t__ IEEE80211_MODE_TURBO_G ; 
#define  IFM_AUTO 134 
#define  IFM_IEEE80211_11A 133 
#define  IFM_IEEE80211_11B 132 
#define  IFM_IEEE80211_11G 131 
#define  IFM_IEEE80211_11NA 130 
#define  IFM_IEEE80211_11NG 129 
#define  IFM_IEEE80211_FH 128 
 int IFM_IEEE80211_TURBO ; 
 int IFM_MODE (int) ; 

__attribute__((used)) static int
media2mode(const struct ifmedia_entry *ime, uint32_t flags, uint16_t *mode)
{
	switch (IFM_MODE(ime->ifm_media)) {
	case IFM_IEEE80211_11A:
		*mode = IEEE80211_MODE_11A;
		break;
	case IFM_IEEE80211_11B:
		*mode = IEEE80211_MODE_11B;
		break;
	case IFM_IEEE80211_11G:
		*mode = IEEE80211_MODE_11G;
		break;
	case IFM_IEEE80211_FH:
		*mode = IEEE80211_MODE_FH;
		break;
	case IFM_IEEE80211_11NA:
		*mode = IEEE80211_MODE_11NA;
		break;
	case IFM_IEEE80211_11NG:
		*mode = IEEE80211_MODE_11NG;
		break;
	case IFM_AUTO:
		*mode = IEEE80211_MODE_AUTO;
		break;
	default:
		return 0;
	}
	/*
	 * Turbo mode is an ``option''.
	 * XXX does not apply to AUTO
	 */
	if (ime->ifm_media & IFM_IEEE80211_TURBO) {
		if (*mode == IEEE80211_MODE_11A) {
			if (flags & IEEE80211_F_TURBOP)
				*mode = IEEE80211_MODE_TURBO_A;
			else
				*mode = IEEE80211_MODE_STURBO_A;
		} else if (*mode == IEEE80211_MODE_11G)
			*mode = IEEE80211_MODE_TURBO_G;
		else
			return 0;
	}
	/* XXX HT40 +/- */
	return 1;
}