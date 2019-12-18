#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  unknown_acct_types; int /*<<< orphan*/  acct_bad_authenticators; int /*<<< orphan*/  malformed_acct_requests; int /*<<< orphan*/  acct_responses; int /*<<< orphan*/  invalid_acct_requests; int /*<<< orphan*/  acct_requests; int /*<<< orphan*/  unknown_types; int /*<<< orphan*/  packets_dropped; int /*<<< orphan*/  bad_authenticators; int /*<<< orphan*/  malformed_access_requests; int /*<<< orphan*/  access_challenges; int /*<<< orphan*/  access_rejects; int /*<<< orphan*/  access_accepts; int /*<<< orphan*/  dup_access_requests; int /*<<< orphan*/  invalid_requests; int /*<<< orphan*/  access_requests; } ;
struct TYPE_4__ {int sec; int usec; } ;
struct radius_server_data {scalar_t__ ipv6; struct radius_client* clients; TYPE_2__ counters; TYPE_1__ start_time; } ;
struct TYPE_6__ {int /*<<< orphan*/  unknown_acct_types; int /*<<< orphan*/  acct_bad_authenticators; int /*<<< orphan*/  malformed_acct_requests; int /*<<< orphan*/  acct_responses; int /*<<< orphan*/  invalid_acct_requests; int /*<<< orphan*/  acct_requests; int /*<<< orphan*/  unknown_types; int /*<<< orphan*/  packets_dropped; int /*<<< orphan*/  bad_authenticators; int /*<<< orphan*/  malformed_access_requests; int /*<<< orphan*/  access_challenges; int /*<<< orphan*/  access_rejects; int /*<<< orphan*/  access_accepts; int /*<<< orphan*/  dup_access_requests; int /*<<< orphan*/  access_requests; } ;
struct radius_client {TYPE_3__ counters; int /*<<< orphan*/  mask; int /*<<< orphan*/  addr; int /*<<< orphan*/  mask6; int /*<<< orphan*/  addr6; struct radius_client* next; } ;
struct os_reltime {int sec; int usec; } ;
typedef  int /*<<< orphan*/  mbuf ;
typedef  int /*<<< orphan*/  abuf ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET6 ; 
 int /*<<< orphan*/  inet_ntoa (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * inet_ntop (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  os_get_reltime (struct os_reltime*) ; 
 int os_snprintf (char*,int,char*,unsigned int,...) ; 
 scalar_t__ os_snprintf_error (int,int) ; 
 int /*<<< orphan*/  os_strlcpy (char*,int /*<<< orphan*/ ,int) ; 

int radius_server_get_mib(struct radius_server_data *data, char *buf,
			  size_t buflen)
{
	int ret, uptime;
	unsigned int idx;
	char *end, *pos;
	struct os_reltime now;
	struct radius_client *cli;

	/* RFC 2619 - RADIUS Authentication Server MIB */

	if (data == NULL || buflen == 0)
		return 0;

	pos = buf;
	end = buf + buflen;

	os_get_reltime(&now);
	uptime = (now.sec - data->start_time.sec) * 100 +
		((now.usec - data->start_time.usec) / 10000) % 100;
	ret = os_snprintf(pos, end - pos,
			  "RADIUS-AUTH-SERVER-MIB\n"
			  "radiusAuthServIdent=hostapd\n"
			  "radiusAuthServUpTime=%d\n"
			  "radiusAuthServResetTime=0\n"
			  "radiusAuthServConfigReset=4\n",
			  uptime);
	if (os_snprintf_error(end - pos, ret)) {
		*pos = '\0';
		return pos - buf;
	}
	pos += ret;

	ret = os_snprintf(pos, end - pos,
			  "radiusAuthServTotalAccessRequests=%u\n"
			  "radiusAuthServTotalInvalidRequests=%u\n"
			  "radiusAuthServTotalDupAccessRequests=%u\n"
			  "radiusAuthServTotalAccessAccepts=%u\n"
			  "radiusAuthServTotalAccessRejects=%u\n"
			  "radiusAuthServTotalAccessChallenges=%u\n"
			  "radiusAuthServTotalMalformedAccessRequests=%u\n"
			  "radiusAuthServTotalBadAuthenticators=%u\n"
			  "radiusAuthServTotalPacketsDropped=%u\n"
			  "radiusAuthServTotalUnknownTypes=%u\n"
			  "radiusAccServTotalRequests=%u\n"
			  "radiusAccServTotalInvalidRequests=%u\n"
			  "radiusAccServTotalResponses=%u\n"
			  "radiusAccServTotalMalformedRequests=%u\n"
			  "radiusAccServTotalBadAuthenticators=%u\n"
			  "radiusAccServTotalUnknownTypes=%u\n",
			  data->counters.access_requests,
			  data->counters.invalid_requests,
			  data->counters.dup_access_requests,
			  data->counters.access_accepts,
			  data->counters.access_rejects,
			  data->counters.access_challenges,
			  data->counters.malformed_access_requests,
			  data->counters.bad_authenticators,
			  data->counters.packets_dropped,
			  data->counters.unknown_types,
			  data->counters.acct_requests,
			  data->counters.invalid_acct_requests,
			  data->counters.acct_responses,
			  data->counters.malformed_acct_requests,
			  data->counters.acct_bad_authenticators,
			  data->counters.unknown_acct_types);
	if (os_snprintf_error(end - pos, ret)) {
		*pos = '\0';
		return pos - buf;
	}
	pos += ret;

	for (cli = data->clients, idx = 0; cli; cli = cli->next, idx++) {
		char abuf[50], mbuf[50];
#ifdef CONFIG_IPV6
		if (data->ipv6) {
			if (inet_ntop(AF_INET6, &cli->addr6, abuf,
				      sizeof(abuf)) == NULL)
				abuf[0] = '\0';
			if (inet_ntop(AF_INET6, &cli->mask6, mbuf,
				      sizeof(mbuf)) == NULL)
				mbuf[0] = '\0';
		}
#endif /* CONFIG_IPV6 */
		if (!data->ipv6) {
			os_strlcpy(abuf, inet_ntoa(cli->addr), sizeof(abuf));
			os_strlcpy(mbuf, inet_ntoa(cli->mask), sizeof(mbuf));
		}

		ret = os_snprintf(pos, end - pos,
				  "radiusAuthClientIndex=%u\n"
				  "radiusAuthClientAddress=%s/%s\n"
				  "radiusAuthServAccessRequests=%u\n"
				  "radiusAuthServDupAccessRequests=%u\n"
				  "radiusAuthServAccessAccepts=%u\n"
				  "radiusAuthServAccessRejects=%u\n"
				  "radiusAuthServAccessChallenges=%u\n"
				  "radiusAuthServMalformedAccessRequests=%u\n"
				  "radiusAuthServBadAuthenticators=%u\n"
				  "radiusAuthServPacketsDropped=%u\n"
				  "radiusAuthServUnknownTypes=%u\n"
				  "radiusAccServTotalRequests=%u\n"
				  "radiusAccServTotalInvalidRequests=%u\n"
				  "radiusAccServTotalResponses=%u\n"
				  "radiusAccServTotalMalformedRequests=%u\n"
				  "radiusAccServTotalBadAuthenticators=%u\n"
				  "radiusAccServTotalUnknownTypes=%u\n",
				  idx,
				  abuf, mbuf,
				  cli->counters.access_requests,
				  cli->counters.dup_access_requests,
				  cli->counters.access_accepts,
				  cli->counters.access_rejects,
				  cli->counters.access_challenges,
				  cli->counters.malformed_access_requests,
				  cli->counters.bad_authenticators,
				  cli->counters.packets_dropped,
				  cli->counters.unknown_types,
				  cli->counters.acct_requests,
				  cli->counters.invalid_acct_requests,
				  cli->counters.acct_responses,
				  cli->counters.malformed_acct_requests,
				  cli->counters.acct_bad_authenticators,
				  cli->counters.unknown_acct_types);
		if (os_snprintf_error(end - pos, ret)) {
			*pos = '\0';
			return pos - buf;
		}
		pos += ret;
	}

	return pos - buf;
}