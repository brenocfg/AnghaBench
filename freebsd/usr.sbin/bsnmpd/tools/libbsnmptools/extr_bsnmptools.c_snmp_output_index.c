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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  scalar_t__ uint32_t ;
struct snmp_toolinfo {int dummy; } ;
struct index {int syntax; int /*<<< orphan*/  tc; int /*<<< orphan*/  snmp_enum; } ;
struct asn_oid {scalar_t__ len; int /*<<< orphan*/ * subs; } ;
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASN_MAXOCTETSTRING ; 
 int /*<<< orphan*/  ASN_MAXOIDLEN ; 
#define  SNMP_SYNTAX_COUNTER 135 
#define  SNMP_SYNTAX_COUNTER64 134 
#define  SNMP_SYNTAX_GAUGE 133 
#define  SNMP_SYNTAX_INTEGER 132 
#define  SNMP_SYNTAX_IPADDRESS 131 
#define  SNMP_SYNTAX_OCTETSTRING 130 
#define  SNMP_SYNTAX_OID 129 
#define  SNMP_SYNTAX_TIMETICKS 128 
 int /*<<< orphan*/  asn_append_oid (struct asn_oid*,struct asn_oid*) ; 
 int /*<<< orphan*/  asn_slice_oid (struct asn_oid*,struct asn_oid*,int,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  memset (struct asn_oid*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snmp_output_counter (struct snmp_toolinfo*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snmp_output_counter64 (struct snmp_toolinfo*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snmp_output_gauge (struct snmp_toolinfo*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snmp_output_int (struct snmp_toolinfo*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snmp_output_ipaddress (struct snmp_toolinfo*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snmp_output_octetindex (struct snmp_toolinfo*,int /*<<< orphan*/ ,struct asn_oid*) ; 
 int /*<<< orphan*/  snmp_output_oid_value (struct snmp_toolinfo*,struct asn_oid*) ; 
 int /*<<< orphan*/  snmp_output_ticks (struct snmp_toolinfo*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int32_t
snmp_output_index(struct snmp_toolinfo *snmptoolctx, struct index *stx,
    struct asn_oid *oid)
{
	uint8_t ip[4];
	uint32_t bytes = 1;
	uint64_t cnt64;
	struct asn_oid temp, out;

	if (oid->len < bytes)
		return (-1);

	memset(&temp, 0, sizeof(struct asn_oid));
	asn_append_oid(&temp, oid);

	switch (stx->syntax) {
	    case SNMP_SYNTAX_INTEGER:
		snmp_output_int(snmptoolctx, stx->snmp_enum, temp.subs[0]);
		break;

	    case SNMP_SYNTAX_OCTETSTRING:
		if ((temp.subs[0] > temp.len -1 ) || (temp.subs[0] >
		    ASN_MAXOCTETSTRING))
			return (-1);
		snmp_output_octetindex(snmptoolctx, stx->tc, &temp);
		bytes += temp.subs[0];
		break;

	    case SNMP_SYNTAX_OID:
		if ((temp.subs[0] > temp.len -1) || (temp.subs[0] >
		    ASN_MAXOIDLEN))
			return (-1);

		bytes += temp.subs[0];
		memset(&out, 0, sizeof(struct asn_oid));
		asn_slice_oid(&out, &temp, 1, bytes);
		snmp_output_oid_value(snmptoolctx, &out);
		break;

	    case SNMP_SYNTAX_IPADDRESS:
		if (temp.len < 4)
			return (-1);
		for (bytes = 0; bytes < 4; bytes++)
			ip[bytes] = temp.subs[bytes];

		snmp_output_ipaddress(snmptoolctx, ip);
		bytes = 4;
		break;

	    case SNMP_SYNTAX_COUNTER:
		snmp_output_counter(snmptoolctx, temp.subs[0]);
		break;

	    case SNMP_SYNTAX_GAUGE:
		snmp_output_gauge(snmptoolctx, temp.subs[0]);
		break;

	    case SNMP_SYNTAX_TIMETICKS:
		snmp_output_ticks(snmptoolctx, temp.subs[0]);
		break;

	    case SNMP_SYNTAX_COUNTER64:
		if (oid->len < 2)
			return (-1);
		bytes = 2;
		memcpy(&cnt64, temp.subs, bytes);
		snmp_output_counter64(snmptoolctx, cnt64);
		break;

	    default:
		return (-1);
	}

	return (bytes);
}