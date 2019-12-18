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
struct hs20_osu_client {size_t server_dnsname_count; char** server_dnsname; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_INFO ; 
 size_t os_strlen (char const*) ; 
 scalar_t__ os_strncasecmp (char const*,char const*,size_t) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,char*) ; 

__attribute__((used)) static int server_dnsname_suffix_match(struct hs20_osu_client *ctx,
				       const char *fqdn)
{
	size_t match_len, len, i;
	const char *val;

	match_len = os_strlen(fqdn);

	for (i = 0; i < ctx->server_dnsname_count; i++) {
		wpa_printf(MSG_INFO,
			   "Checking suffix match against server dNSName %s",
			   ctx->server_dnsname[i]);
		val = ctx->server_dnsname[i];
		len = os_strlen(val);

		if (match_len > len)
			continue;

		if (os_strncasecmp(val + len - match_len, fqdn, match_len) != 0)
			continue; /* no match */

		if (match_len == len)
			return 1; /* exact match */

		if (val[len - match_len - 1] == '.')
			return 1; /* full label match completes suffix match */

		/* Reject due to incomplete label match */
	}

	/* None of the dNSName(s) matched */
	return 0;
}