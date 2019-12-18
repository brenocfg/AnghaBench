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
struct snmp_toolinfo {int dummy; } ;
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  OUTPUT_QUIET ; 
 int /*<<< orphan*/  OUTPUT_SHORT ; 
 int /*<<< orphan*/  OUTPUT_TABULAR ; 
 int /*<<< orphan*/  OUTPUT_VERBOSE ; 
 int /*<<< orphan*/  SET_OUTPUT (struct snmp_toolinfo*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (char*) ; 
 scalar_t__ strncasecmp (char*,char*,scalar_t__) ; 
 int /*<<< orphan*/  warnx (char*,char*) ; 

int32_t
parse_output(struct snmp_toolinfo *snmptoolctx, char *opt_arg)
{
	assert(opt_arg != NULL);

	if (strlen(opt_arg) > strlen("verbose")) {
		warnx( "Invalid output option - %s",opt_arg);
		return (-1);
	}

	if (strncasecmp(opt_arg, "short", strlen(opt_arg)) == 0)
		SET_OUTPUT(snmptoolctx, OUTPUT_SHORT);
	else if (strncasecmp(opt_arg, "verbose", strlen(opt_arg)) == 0)
		SET_OUTPUT(snmptoolctx, OUTPUT_VERBOSE);
	else if (strncasecmp(opt_arg,"tabular", strlen(opt_arg)) == 0)
		SET_OUTPUT(snmptoolctx, OUTPUT_TABULAR);
	else if (strncasecmp(opt_arg, "quiet", strlen(opt_arg)) == 0)
		SET_OUTPUT(snmptoolctx, OUTPUT_QUIET);
	else {
		warnx( "Invalid output option - %s", opt_arg);
		return (-1);
	}

	return (2);
}