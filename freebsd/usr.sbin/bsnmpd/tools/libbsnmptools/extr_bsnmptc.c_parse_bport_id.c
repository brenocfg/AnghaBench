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
 int SNMP_BPORT_OCTETS ; 
 int SNMP_MAX_BPORT_PRIORITY ; 
 int /*<<< orphan*/  SNMP_SYNTAX_OCTETSTRING ; 
 int errno ; 
 int /*<<< orphan*/ * malloc (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int*,int) ; 
 int /*<<< orphan*/  strerror (int) ; 
 int strtoul (char*,char**,int) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warnx (char*,int) ; 

__attribute__((used)) static int32_t
parse_bport_id(struct snmp_value *value, char *string)
{
	char *endptr;
	int saved_errno;
	uint32_t v;
	uint8_t	bport_id[SNMP_BPORT_OCTETS];

	/* Read the priority. */
	saved_errno = errno;
	errno = 0;
	v = strtoul(string, &endptr, 10);

	if (v > SNMP_MAX_BPORT_PRIORITY || errno != 0 || *endptr != '.') {
		errno = saved_errno;
		warnx("Bad bridge port priority value %d", v);
		return (-1);
	}

	bport_id[0] = v;

	string = endptr + 1;
	v = strtoul(string, &endptr, 16);
	if (v > 0xff) {
		warnx("Bad port number - %d", v);
		return (-1);
	}

	bport_id[1] = v;

	if ((value->v.octetstring.octets = malloc(SNMP_BPORT_OCTETS)) == NULL) {
		syslog(LOG_ERR, "malloc failed: %s", strerror(errno));
		return (-1);
	}

	value->v.octetstring.len = SNMP_BPORT_OCTETS;
	memcpy(value->v.octetstring.octets, bport_id, SNMP_BPORT_OCTETS);
	value->syntax = SNMP_SYNTAX_OCTETSTRING;
	return (1);
}