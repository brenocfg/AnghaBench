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
struct snmp_toolinfo {scalar_t__ objects; int /*<<< orphan*/  snmp_objectlist; } ;
struct snmp_object {int dummy; } ;
typedef  scalar_t__ (* snmp_verify_inoid_f ) (struct snmp_toolinfo*,struct snmp_object*,char*) ;
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  SLIST_INSERT_HEAD (int /*<<< orphan*/ *,struct snmp_object*,int /*<<< orphan*/ ) ; 
 scalar_t__ SNMP_MAX_BINDINGS ; 
 struct snmp_object* calloc (int,int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  free (struct snmp_object*) ; 
 int /*<<< orphan*/  link ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warnx (char*,char*) ; 

int32_t
snmp_object_add(struct snmp_toolinfo *snmptoolctx, snmp_verify_inoid_f func,
    char *string)
{
	struct snmp_object *obj;

	if (snmptoolctx == NULL)
		return (-1);

	/* XXX-BZ does that chack make sense? */
	if (snmptoolctx->objects >= SNMP_MAX_BINDINGS) {
		warnx("Too many bindings in PDU - %u", snmptoolctx->objects + 1);
		return (-1);
	}

	if ((obj = calloc(1, sizeof(struct snmp_object))) == NULL) {
		syslog(LOG_ERR, "malloc() failed: %s", strerror(errno));
		return (-1);
	}

	if (func(snmptoolctx, obj, string) < 0) {
		warnx("Invalid OID - %s", string);
		free(obj);
		return (-1);
	}

	snmptoolctx->objects++;
	SLIST_INSERT_HEAD(&snmptoolctx->snmp_objectlist, obj, link);

	return (1);
}