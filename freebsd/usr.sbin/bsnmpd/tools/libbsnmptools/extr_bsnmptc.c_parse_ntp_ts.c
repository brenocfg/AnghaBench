#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint32_t ;
struct TYPE_3__ {int len; int /*<<< orphan*/ * octets; } ;
struct TYPE_4__ {TYPE_1__ octetstring; } ;
struct snmp_value {int /*<<< orphan*/  syntax; TYPE_2__ v; } ;
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERR ; 
 int SNMP_NTP_TS_OCTETS ; 
 int /*<<< orphan*/  SNMP_SYNTAX_OCTETSTRING ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/ * malloc (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int*,int) ; 
 int /*<<< orphan*/  strerror (scalar_t__) ; 
 int strtoul (char*,char**,int) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warnx (char*,char*) ; 

__attribute__((used)) static int32_t
parse_ntp_ts(struct snmp_value *sv, char *val)
{
	char *endptr;
	int32_t i, d, saved_errno;
	uint32_t v;
	uint8_t	ntp_ts[SNMP_NTP_TS_OCTETS];

	saved_errno = errno;
	errno = 0;
	v = strtoul(val, &endptr, 10);
	if (errno != 0 || (v / 1000) > 9) {
		errno = saved_errno;
		warnx("Integer value %s not supported", val);
		return (-1);
	} else
		errno = saved_errno;

	if (*endptr != '.') {
		warnx("Failed reading octet - %s", val);
		return (-1);
	}

	for (i = 0, d = 1000; i < 4; i++) {
		ntp_ts[i] = v / d;
		v = v % d;
		d = d / 10;
	}
	val = endptr + 1;

	saved_errno = errno;
	errno = 0;
	v = strtoul(val, &endptr, 10);
	if (errno != 0 || (v / 1000) > 9) {
		errno = saved_errno;
		warnx("Integer value %s not supported", val);
		return (-1);
	} else
		errno = saved_errno;

	for (i = 0, d = 1000; i < 4; i++) {
		ntp_ts[i + 4] = v / d;
		v = v % d;
		d = d / 10;
	}

	if ((sv->v.octetstring.octets = malloc(SNMP_NTP_TS_OCTETS)) == NULL) {
		syslog(LOG_ERR, "malloc failed: %s", strerror(errno));
		return (-1);
	}

	sv->v.octetstring.len = SNMP_NTP_TS_OCTETS;
	memcpy(sv->v.octetstring.octets, ntp_ts, SNMP_NTP_TS_OCTETS);
	sv->syntax = SNMP_SYNTAX_OCTETSTRING;
	return (1);
}