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
struct TYPE_3__ {scalar_t__ len; int /*<<< orphan*/ * octets; } ;
struct TYPE_4__ {TYPE_1__ octetstring; } ;
struct snmp_value {TYPE_2__ v; int /*<<< orphan*/  syntax; } ;
typedef  int int32_t ;

/* Variables and functions */
 scalar_t__ ASN_MAXOCTETSTRING ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  SNMP_SYNTAX_OCTETSTRING ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/ * malloc (scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warnx (char*,scalar_t__) ; 

__attribute__((used)) static int32_t
add_octstring_syntax(struct snmp_value *dst, struct snmp_value *src)
{
	if (src->v.octetstring.len > ASN_MAXOCTETSTRING) {
		warnx("OctetString len too big - %u", src->v.octetstring.len);
		return (-1);
	}

	if ((dst->v.octetstring.octets = malloc(src->v.octetstring.len)) ==
	    NULL) {
		syslog(LOG_ERR, "malloc() failed - %s", strerror(errno));
		return (-1);
	}

	memcpy(dst->v.octetstring.octets, src->v.octetstring.octets,
	    src->v.octetstring.len);
	dst->syntax = SNMP_SYNTAX_OCTETSTRING;
	dst->v.octetstring.len = src->v.octetstring.len;

	return(0);
}