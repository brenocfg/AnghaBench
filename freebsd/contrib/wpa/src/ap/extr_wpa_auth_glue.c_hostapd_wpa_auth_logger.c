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
typedef  int /*<<< orphan*/  u8 ;
struct hostapd_data {int dummy; } ;
typedef  int logger_level ;

/* Variables and functions */
 int HOSTAPD_LEVEL_DEBUG ; 
 int HOSTAPD_LEVEL_INFO ; 
 int HOSTAPD_LEVEL_WARNING ; 
 int /*<<< orphan*/  HOSTAPD_MODULE_WPA ; 
#define  LOGGER_DEBUG 130 
#define  LOGGER_INFO 129 
#define  LOGGER_WARNING 128 
 int /*<<< orphan*/  hostapd_logger (struct hostapd_data*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int,char*,char const*) ; 

__attribute__((used)) static void hostapd_wpa_auth_logger(void *ctx, const u8 *addr,
				    logger_level level, const char *txt)
{
#ifndef CONFIG_NO_HOSTAPD_LOGGER
	struct hostapd_data *hapd = ctx;
	int hlevel;

	switch (level) {
	case LOGGER_WARNING:
		hlevel = HOSTAPD_LEVEL_WARNING;
		break;
	case LOGGER_INFO:
		hlevel = HOSTAPD_LEVEL_INFO;
		break;
	case LOGGER_DEBUG:
	default:
		hlevel = HOSTAPD_LEVEL_DEBUG;
		break;
	}

	hostapd_logger(hapd, addr, HOSTAPD_MODULE_WPA, hlevel, "%s", txt);
#endif /* CONFIG_NO_HOSTAPD_LOGGER */
}