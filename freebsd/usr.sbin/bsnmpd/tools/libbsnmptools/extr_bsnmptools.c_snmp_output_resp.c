#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
struct snmp_toolinfo {int dummy; } ;
struct snmp_pdu {size_t nbindings; TYPE_1__* bindings; } ;
struct snmp_object {int /*<<< orphan*/  info; } ;
struct asn_oid {int dummy; } ;
typedef  int int32_t ;
struct TYPE_3__ {int /*<<< orphan*/  var; } ;

/* Variables and functions */
 int ASN_OIDSTRLEN ; 
 scalar_t__ GET_OUTPUT (struct snmp_toolinfo*) ; 
 int /*<<< orphan*/  ISSET_NUMERIC (struct snmp_toolinfo*) ; 
 scalar_t__ OUTPUT_QUIET ; 
 int /*<<< orphan*/  asn_is_suboid (struct asn_oid*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  asn_oid2str_r (int /*<<< orphan*/ *,char*) ; 
 struct snmp_object* calloc (int,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  free (struct snmp_object*) ; 
 scalar_t__ snmp_fill_object (struct snmp_toolinfo*,struct snmp_object*,TYPE_1__*) ; 
 int snmp_output_numval (struct snmp_toolinfo*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snmp_output_object (struct snmp_toolinfo*,struct snmp_object*) ; 
 int /*<<< orphan*/  stdout ; 

int32_t
snmp_output_resp(struct snmp_toolinfo *snmptoolctx, struct snmp_pdu *pdu,
    struct asn_oid *root)
{
	struct snmp_object *object;
	char p[ASN_OIDSTRLEN];
	int32_t error;
	uint32_t i;

	if ((object = calloc(1, sizeof(struct snmp_object))) == NULL)
		return (-1);

	i = error = 0;
	while (i < pdu->nbindings) {
		if (root != NULL && !(asn_is_suboid(root,
		    &(pdu->bindings[i].var))))
			break;

		if (GET_OUTPUT(snmptoolctx) != OUTPUT_QUIET) {
			if (!ISSET_NUMERIC(snmptoolctx) &&
			    (snmp_fill_object(snmptoolctx, object,
			    &(pdu->bindings[i])) > 0))
				snmp_output_object(snmptoolctx, object);
			else {
				asn_oid2str_r(&(pdu->bindings[i].var), p);
				fprintf(stdout, "%s", p);
			}
		}
		error |= snmp_output_numval(snmptoolctx, &(pdu->bindings[i]),
		    object->info);
		i++;
	}

	free(object);
	object = NULL;

	if (error)
		return (-1);

	return (i);
}