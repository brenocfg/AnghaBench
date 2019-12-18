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
 int SNMP_BRIDGEID_OCTETS ; 
 int SNMP_MAX_BRIDGE_PRIORITY ; 
 int /*<<< orphan*/  SNMP_SYNTAX_OCTETSTRING ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/ * malloc (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int*,int) ; 
 int /*<<< orphan*/  strerror (scalar_t__) ; 
 int strtoul (char*,char**,int) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warnx (char*,...) ; 

__attribute__((used)) static int32_t
parse_bridge_id(struct snmp_value *sv, char *string)
{
	char *endptr;
	int32_t i, saved_errno;
	uint32_t v;
	uint8_t	bridge_id[SNMP_BRIDGEID_OCTETS];

	/* Read the priority. */
	saved_errno = errno;
	errno = 0;
	v = strtoul(string, &endptr, 10);

	if (v > SNMP_MAX_BRIDGE_PRIORITY || errno != 0 || *endptr != '.') {
		errno = saved_errno;
		warnx("Bad bridge priority value %d", v);
		return (-1);
	}

	bridge_id[0] = (v & 0xff00);
	bridge_id[1] = (v & 0xff);

	string = endptr + 1;

	for (i = 0; i < 5; i++) {
		v = strtoul(string, &endptr, 16);
		if (v > 0xff) {
			warnx("Integer value %s not supported", string);
			return (-1);
		}
		if(*endptr != ':') {
			warnx("Failed reading octet - %s", string);
			return (-1);
		}
		bridge_id[i + 2] = v;
		string = endptr + 1;
	}

	/* The last one - don't check the ending char here. */
	v = strtoul(string, &endptr, 16);
	if (v > 0xff) {
		warnx("Integer value %s not supported", string);
		return (-1);
	}
	bridge_id[7] = v;

	if ((sv->v.octetstring.octets = malloc(SNMP_BRIDGEID_OCTETS)) == NULL) {
		syslog(LOG_ERR, "malloc failed: %s", strerror(errno));
		return (-1);
	}

	sv->v.octetstring.len = SNMP_BRIDGEID_OCTETS;
	memcpy(sv->v.octetstring.octets, bridge_id, SNMP_BRIDGEID_OCTETS);
	sv->syntax = SNMP_SYNTAX_OCTETSTRING;
	return (1);
}