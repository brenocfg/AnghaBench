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
struct dpp_bootstrap_info {char* info; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  dpp_uri_valid_info (char*) ; 
 char* os_malloc (int) ; 
 int /*<<< orphan*/  os_memcpy (char*,char const*,int) ; 
 char* os_strchr (char const*,char) ; 
 int os_strlen (char const*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

int dpp_parse_uri_info(struct dpp_bootstrap_info *bi, const char *info)
{
	const char *end;

	if (!info)
		return 0;

	end = os_strchr(info, ';');
	if (!end)
		end = info + os_strlen(info);
	bi->info = os_malloc(end - info + 1);
	if (!bi->info)
		return -1;
	os_memcpy(bi->info, info, end - info);
	bi->info[end - info] = '\0';
	wpa_printf(MSG_DEBUG, "DPP: URI(information): %s", bi->info);
	if (!dpp_uri_valid_info(bi->info)) {
		wpa_printf(MSG_DEBUG, "DPP: Invalid URI information payload");
		return -1;
	}

	return 0;
}