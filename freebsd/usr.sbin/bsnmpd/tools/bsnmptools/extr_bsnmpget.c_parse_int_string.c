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
struct TYPE_5__ {int integer; } ;
struct TYPE_6__ {TYPE_2__ v; } ;
struct snmp_object {TYPE_3__ val; TYPE_1__* info; } ;
typedef  int int32_t ;
struct TYPE_4__ {int /*<<< orphan*/  snmp_enum; } ;

/* Variables and functions */
 int enum_number_lookup (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ isdigit (char) ; 
 int parse_int (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  warnx (char*,char*) ; 

__attribute__((used)) static int32_t
parse_int_string(struct snmp_object *object, char *val)
{
	int32_t	v;

	if (isdigit(val[0]))
		return ((parse_int(&(object->val), val)));

	if (object->info == NULL) {
		warnx("Unknown enumerated integer type - %s", val);
		return (-1);
	}
	if ((v = enum_number_lookup(object->info->snmp_enum, val)) < 0)
		warnx("Unknown enumerated integer type - %s", val);

	object->val.v.integer = v;
	return (1);
}