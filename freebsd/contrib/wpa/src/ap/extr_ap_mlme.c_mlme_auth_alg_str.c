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
#define  WLAN_AUTH_FT 130 
#define  WLAN_AUTH_OPEN 129 
#define  WLAN_AUTH_SHARED_KEY 128 

__attribute__((used)) static const char * mlme_auth_alg_str(int alg)
{
	switch (alg) {
	case WLAN_AUTH_OPEN:
		return "OPEN_SYSTEM";
	case WLAN_AUTH_SHARED_KEY:
		return "SHARED_KEY";
	case WLAN_AUTH_FT:
		return "FT";
	}

	return "unknown";
}