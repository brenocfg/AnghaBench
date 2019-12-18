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
struct snmp_toolinfo {scalar_t__ objects; int /*<<< orphan*/  passwd; } ;
typedef  int int32_t ;
struct TYPE_3__ {scalar_t__ engine_len; int /*<<< orphan*/  engine_id; } ;
struct TYPE_4__ {scalar_t__ version; TYPE_1__ engine; int /*<<< orphan*/  user; } ;

/* Variables and functions */
#define  BSNMPGET 130 
#define  BSNMPSET 129 
#define  BSNMPWALK 128 
 scalar_t__ GET_OUTPUT (struct snmp_toolinfo*) ; 
 scalar_t__ GET_PDUTYPE (struct snmp_toolinfo*) ; 
 scalar_t__ ISSET_EDISCOVER (struct snmp_toolinfo*) ; 
 scalar_t__ ISSET_LOCALKEY (struct snmp_toolinfo*) ; 
 scalar_t__ OUTPUT_VERBOSE ; 
 int /*<<< orphan*/  SET_EDISCOVER (struct snmp_toolinfo*) ; 
 scalar_t__ SNMP_CODE_OK ; 
 scalar_t__ SNMP_PDU_GETBULK ; 
 scalar_t__ SNMP_V1 ; 
 scalar_t__ SNMP_V3 ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int program ; 
 char* program_name ; 
 TYPE_2__ snmp_client ; 
 int /*<<< orphan*/  snmp_close () ; 
 scalar_t__ snmp_discover_engine (int /*<<< orphan*/ ) ; 
 scalar_t__ snmp_get_local_keys (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ snmp_import_all (struct snmp_toolinfo*) ; 
 scalar_t__ snmp_object_add (struct snmp_toolinfo*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ snmp_open (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snmp_output_engine () ; 
 int /*<<< orphan*/  snmp_output_keys () ; 
 scalar_t__ snmp_passwd_to_keys (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snmp_tool_freeall (struct snmp_toolinfo*) ; 
 int /*<<< orphan*/  snmpset_parse_oid ; 
 int snmptool_get (struct snmp_toolinfo*) ; 
 scalar_t__ snmptool_init (struct snmp_toolinfo*) ; 
 int snmptool_parse_options (struct snmp_toolinfo*,int,char**) ; 
 int snmptool_set (struct snmp_toolinfo*) ; 
 int snmptool_walk (struct snmp_toolinfo*) ; 
 int /*<<< orphan*/  snmptools_parse_oid ; 
 int /*<<< orphan*/  snmpwalk_add_default ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcmp (char*,char*) ; 
 char* strrchr (char*,char) ; 
 int /*<<< orphan*/  usage () ; 
 int /*<<< orphan*/  warn (char*) ; 

int
main(int argc, char ** argv)
{
	struct snmp_toolinfo snmptoolctx;
	int32_t oid_cnt, last_oid, opt_num;
	int rc = 0;

	/* Make sure program_name is set and valid. */
	if (*argv == NULL)
		program_name = "snmptool";
	else {
		program_name = strrchr(*argv, '/');
		if (program_name != NULL)
			program_name++;
		else
			program_name = *argv;
	}

	if (program_name == NULL) {
		fprintf(stderr, "Error: No program name?\n");
		exit (1);
	} else if (strcmp(program_name, "bsnmpget") == 0)
		program = BSNMPGET;
	else if (strcmp(program_name, "bsnmpwalk") == 0)
		program = BSNMPWALK;
	else if (strcmp(program_name, "bsnmpset") == 0)
		program = BSNMPSET;
	else {
		fprintf(stderr, "Unknown snmp tool name '%s'.\n", program_name);
		exit (1);
	}

	/* Initialize. */
	if (snmptool_init(&snmptoolctx) < 0)
		exit (1);

	if ((opt_num = snmptool_parse_options(&snmptoolctx, argc, argv)) < 0) {
		snmp_tool_freeall(&snmptoolctx);
		/* On -h (help) exit without error. */
		if (opt_num == -2)
			exit(0);
		else
			exit(1);
	}

	oid_cnt = argc - opt_num - 1;
	if (oid_cnt == 0) {
		switch (program) {
		case BSNMPGET:
			if (!ISSET_EDISCOVER(&snmptoolctx) &&
			    !ISSET_LOCALKEY(&snmptoolctx)) {
				fprintf(stderr, "No OID given.\n");
				usage();
				snmp_tool_freeall(&snmptoolctx);
				exit(1);
			}
			break;

		case BSNMPWALK:
			if (snmp_object_add(&snmptoolctx, snmpwalk_add_default,
			    NULL) < 0) {
				fprintf(stderr,
				    "Error setting default subtree.\n");
				snmp_tool_freeall(&snmptoolctx);
				exit(1);
			}
			break;

		case BSNMPSET:
			fprintf(stderr, "No OID given.\n");
			usage();
			snmp_tool_freeall(&snmptoolctx);
			exit(1);
		}
	}

	if (snmp_import_all(&snmptoolctx) < 0) {
		snmp_tool_freeall(&snmptoolctx);
		exit(1);
	}

	/* A simple sanity check - can not send GETBULK when using SNMPv1. */
	if (program == BSNMPGET && snmp_client.version == SNMP_V1 &&
	    GET_PDUTYPE(&snmptoolctx) == SNMP_PDU_GETBULK) {
		fprintf(stderr, "Cannot send GETBULK PDU with SNMPv1.\n");
		snmp_tool_freeall(&snmptoolctx);
		exit(1);
	}

	for (last_oid = argc - 1; oid_cnt > 0; last_oid--, oid_cnt--) {
		if ((snmp_object_add(&snmptoolctx, (program == BSNMPSET) ?
		    snmpset_parse_oid : snmptools_parse_oid,
		    argv[last_oid])) < 0) {
			fprintf(stderr, "Error parsing OID string '%s'.\n",
			    argv[last_oid]);
			snmp_tool_freeall(&snmptoolctx);
			exit(1);
		}
	}

	if (snmp_open(NULL, NULL, NULL, NULL)) {
		warn("Failed to open snmp session");
		snmp_tool_freeall(&snmptoolctx);
		exit(1);
	}

	if (snmp_client.version == SNMP_V3 && snmp_client.engine.engine_len == 0)
		SET_EDISCOVER(&snmptoolctx);

	if (ISSET_EDISCOVER(&snmptoolctx) &&
	    snmp_discover_engine(snmptoolctx.passwd) < 0) {
		warn("Unknown SNMP Engine ID");
		rc = 1;
		goto cleanup;
	}

	if (GET_OUTPUT(&snmptoolctx) == OUTPUT_VERBOSE ||
	    ISSET_EDISCOVER(&snmptoolctx))
		snmp_output_engine();

	if (snmp_client.version == SNMP_V3 && ISSET_LOCALKEY(&snmptoolctx) &&
	    !ISSET_EDISCOVER(&snmptoolctx)) {
		if (snmp_passwd_to_keys(&snmp_client.user,
		    snmptoolctx.passwd) != SNMP_CODE_OK ||
		    snmp_get_local_keys(&snmp_client.user,
		    snmp_client.engine.engine_id,
		    snmp_client.engine.engine_len) != SNMP_CODE_OK) {
		    	warn("Failed to get keys");
			rc = 1;
			goto cleanup;
		}
	}

	if (GET_OUTPUT(&snmptoolctx) == OUTPUT_VERBOSE ||
	    ISSET_EDISCOVER(&snmptoolctx))
		snmp_output_keys();

	if (ISSET_EDISCOVER(&snmptoolctx) && snmptoolctx.objects == 0)
		goto cleanup;

	switch (program) {
	case BSNMPGET:
		rc = snmptool_get(&snmptoolctx);
		break;
	case BSNMPWALK:
		rc = snmptool_walk(&snmptoolctx);
		break;
	case BSNMPSET:
		rc = snmptool_set(&snmptoolctx);
		break;
	}


cleanup:
	snmp_tool_freeall(&snmptoolctx);
	snmp_close();

	exit(rc);
}