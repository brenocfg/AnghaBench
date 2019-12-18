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
struct TYPE_3__ {size_t len; int /*<<< orphan*/ * octets; } ;
struct TYPE_4__ {TYPE_1__ octetstring; } ;
struct snmp_value {int /*<<< orphan*/  syntax; TYPE_2__ v; } ;
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERR ; 
 size_t MAX_OCTSTRING_LEN ; 
 int /*<<< orphan*/  SNMP_SYNTAX_OCTETSTRING ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/ * malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,char*,size_t) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 size_t strlen (char*) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warnx (char*,size_t) ; 

__attribute__((used)) static int32_t
parse_octetstring(struct snmp_value *value, char *val)
{
	size_t len;

	if ((len = strlen(val)) >= MAX_OCTSTRING_LEN) {
		warnx("Octetstring too long - %d is max allowed",
		    MAX_OCTSTRING_LEN - 1);
		return (-1);
	}

	if ((value->v.octetstring.octets = malloc(len)) == NULL) {
		value->v.octetstring.len = 0;
		syslog(LOG_ERR, "malloc failed: %s", strerror(errno));
		return (-1);
	}

	value->v.octetstring.len = len;
	memcpy(value->v.octetstring.octets, val, len);
	value->syntax = SNMP_SYNTAX_OCTETSTRING;

	return (0);
}