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
typedef  size_t uint ;
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_4__ {size_t len; int /*<<< orphan*/ * octets; } ;
struct TYPE_5__ {TYPE_1__ octetstring; } ;
struct TYPE_6__ {size_t* subs; int /*<<< orphan*/  len; } ;
struct snmp_value {int /*<<< orphan*/  syntax; TYPE_2__ v; TYPE_3__ var; } ;
struct bridge_if {size_t* bif_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNMP_SYNTAX_OCTETSTRING ; 
 int /*<<< orphan*/  bcopy (size_t*,int /*<<< orphan*/ *,size_t) ; 
 scalar_t__ malloc (size_t) ; 
 TYPE_3__ oid_begemotBrigeName ; 
 size_t strlen (size_t*) ; 

__attribute__((used)) static struct snmp_value*
bridge_basename_var(struct bridge_if *bif, struct snmp_value* b_val)
{
	uint i;

	b_val->var = oid_begemotBrigeName;
	b_val->var.subs[b_val->var.len++] = strlen(bif->bif_name);

	if ((b_val->v.octetstring.octets = (u_char *)
	    malloc(strlen(bif->bif_name))) == NULL)
		return (NULL);

	for (i = 0; i < strlen(bif->bif_name); i++)
		b_val->var.subs[b_val->var.len++] = bif->bif_name[i];

	b_val->v.octetstring.len = strlen(bif->bif_name);
	bcopy(bif->bif_name, b_val->v.octetstring.octets,
	    strlen(bif->bif_name));
	b_val->syntax = SNMP_SYNTAX_OCTETSTRING;

	return (b_val);
}