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
typedef  scalar_t__ u_long ;
typedef  scalar_t__ u_char ;
struct TYPE_3__ {int /*<<< orphan*/ * octets; scalar_t__ len; } ;
struct TYPE_4__ {TYPE_1__ octetstring; } ;
struct snmp_value {TYPE_2__ v; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int SNMP_ERR_NOERROR ; 
 int SNMP_ERR_RES_UNAVAIL ; 
 int /*<<< orphan*/ * malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,scalar_t__ const*,size_t) ; 

__attribute__((used)) static int
bits_get(struct snmp_value *value, const u_char *ptr, ssize_t len)
{
	int size;

	if (ptr == NULL) {
		value->v.octetstring.len = 0;
		value->v.octetstring.octets = NULL;
		return (SNMP_ERR_NOERROR);
	}

	/* Determine length - up to 8 octets supported so far. */
	for (size = len; size > 0; size--)
		if (ptr[size - 1] != 0)
			break;
	if (size == 0)
		size = 1;

	value->v.octetstring.len = (u_long)size;
	if ((value->v.octetstring.octets = malloc((size_t)size)) == NULL)
		return (SNMP_ERR_RES_UNAVAIL);
	memcpy(value->v.octetstring.octets, ptr, (size_t)size);
	return (SNMP_ERR_NOERROR);
}