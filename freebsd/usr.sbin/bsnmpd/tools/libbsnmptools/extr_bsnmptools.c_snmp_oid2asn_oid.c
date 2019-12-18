#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct snmp_toolinfo {int dummy; } ;
struct TYPE_5__ {scalar_t__ len; } ;
struct TYPE_4__ {TYPE_2__ var; } ;
struct snmp_object {TYPE_1__ val; } ;
struct asn_oid {int dummy; } ;
typedef  int int32_t ;
typedef  int /*<<< orphan*/  asn_subid_t ;

/* Variables and functions */
 int MAXSTR ; 
 int /*<<< orphan*/  asn_append_oid (struct asn_oid*,TYPE_2__*) ; 
 scalar_t__ isalpha (char) ; 
 int /*<<< orphan*/  memset (struct snmp_object*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ snmp_lookup_enumoid (struct snmp_toolinfo*,struct snmp_object*,char*) ; 
 char* snmp_parse_suboid (char*,TYPE_2__*) ; 
 scalar_t__ snmp_suboid_append (struct asn_oid*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int) ; 
 int /*<<< orphan*/  warnx (char*,char*) ; 

__attribute__((used)) static char *
snmp_oid2asn_oid(struct snmp_toolinfo *snmptoolctx, char *str,
    struct asn_oid *oid)
{
	int32_t i;
	char string[MAXSTR + 1], *endptr;
	struct snmp_object obj;

	for (i = 0; i < MAXSTR; i++)
		if (isalpha (*(str + i)) == 0)
			break;

	endptr = str + i;
	memset(&obj, 0, sizeof(struct snmp_object));
	if (i == 0) {
		if ((endptr = snmp_parse_suboid(str, &(obj.val.var))) == NULL)
			return (NULL);
		if (snmp_suboid_append(oid, (asn_subid_t) obj.val.var.len) < 0)
			return (NULL);
	} else {
		strlcpy(string, str, i + 1);
		if (snmp_lookup_enumoid(snmptoolctx, &obj, string) < 0) {
			warnx("Unknown string - %s", string);
			return (NULL);
		}
	}

	asn_append_oid(oid, &(obj.val.var));
	return (endptr);
}