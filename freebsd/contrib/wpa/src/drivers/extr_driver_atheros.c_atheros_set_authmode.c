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

/* Variables and functions */
 int IEEE80211_AUTH_AUTO ; 
 int IEEE80211_AUTH_OPEN ; 
 int IEEE80211_AUTH_SHARED ; 
 int /*<<< orphan*/  IEEE80211_PARAM_AUTHMODE ; 
 int WPA_AUTH_ALG_OPEN ; 
 int WPA_AUTH_ALG_SHARED ; 
 int set80211param (void*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int atheros_set_authmode(void *priv, int auth_algs)
{
	int authmode;

	if ((auth_algs & WPA_AUTH_ALG_OPEN) &&
	    (auth_algs & WPA_AUTH_ALG_SHARED))
		authmode = IEEE80211_AUTH_AUTO;
	else if (auth_algs & WPA_AUTH_ALG_OPEN)
		authmode = IEEE80211_AUTH_OPEN;
	else if (auth_algs & WPA_AUTH_ALG_SHARED)
		authmode = IEEE80211_AUTH_SHARED;
	else
		return -1;

	return set80211param(priv, IEEE80211_PARAM_AUTHMODE, authmode);
}