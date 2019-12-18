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
 int SNMP_PHYSADDR_OCTETS ; 
 int /*<<< orphan*/  SNMP_SYNTAX_OCTETSTRING ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/ * malloc (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int*,int) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int strtoul (char*,char**,int) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warnx (char*,char*) ; 

__attribute__((used)) static int32_t
parse_physaddress(struct snmp_value *sv, char *val)
{
	char *endptr;
	int32_t i;
	uint32_t v;
	uint8_t	phys_addr[SNMP_PHYSADDR_OCTETS];

	for (i = 0; i < 5; i++) {
		v = strtoul(val, &endptr, 16);
		if (v > 0xff) {
			warnx("Integer value %s not supported", val);
			return (-1);
		}
		if(*endptr != ':') {
			warnx("Failed reading octet - %s", val);
			return (-1);
		}
		phys_addr[i] = v;
		val = endptr + 1;
	}

	/* The last one - don't check the ending char here. */
	v = strtoul(val, &endptr, 16);
	if (v > 0xff) {
		warnx("Integer value %s not supported", val);
		return (-1);
	}
	phys_addr[5] = v;

	if ((sv->v.octetstring.octets = malloc(SNMP_PHYSADDR_OCTETS)) == NULL) {
		syslog(LOG_ERR, "malloc failed: %s", strerror(errno));
		return (-1);
	}

	sv->v.octetstring.len = SNMP_PHYSADDR_OCTETS;
	memcpy(sv->v.octetstring.octets, phys_addr, SNMP_PHYSADDR_OCTETS);
	sv->syntax = SNMP_SYNTAX_OCTETSTRING;
	return (1);
}