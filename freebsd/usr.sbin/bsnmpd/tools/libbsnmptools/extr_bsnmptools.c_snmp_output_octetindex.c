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
typedef  scalar_t__ uint8_t ;
typedef  size_t uint32_t ;
typedef  scalar_t__ u_char ;
struct snmp_toolinfo {int dummy; } ;
struct asn_oid {size_t* subs; } ;
typedef  enum snmp_tc { ____Placeholder_snmp_tc } snmp_tc ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  free (scalar_t__*) ; 
 scalar_t__* malloc (size_t) ; 
 int /*<<< orphan*/  snmp_output_octetstring (struct snmp_toolinfo*,int,size_t,scalar_t__*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
snmp_output_octetindex(struct snmp_toolinfo *snmptoolctx, enum snmp_tc tc,
    struct asn_oid *oid)
{
	uint32_t i;
	uint8_t *s;

	if ((s = malloc(oid->subs[0] + 1)) == NULL)
		syslog(LOG_ERR, "malloc failed - %s", strerror(errno));
	else {
		for (i = 0; i < oid->subs[0]; i++)
			s[i] = (u_char) (oid->subs[i + 1]);

		snmp_output_octetstring(snmptoolctx, tc, oid->subs[0], s);
		free(s);
	}
}