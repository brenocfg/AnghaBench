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
typedef  int int32_t ;
struct TYPE_3__ {scalar_t__ trans; int /*<<< orphan*/ * chost; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  SNMP_DEFAULT_LOCAL ; 
 scalar_t__ SNMP_TRANS_UDP ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/ * malloc (scalar_t__) ; 
 TYPE_1__ snmp_client ; 
 scalar_t__ snmp_parse_server (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

int32_t
parse_server(char *opt_arg)
{
	assert(opt_arg != NULL);

	if (snmp_parse_server(&snmp_client, opt_arg) < 0)
		return (-1);

	if (snmp_client.trans > SNMP_TRANS_UDP && snmp_client.chost == NULL) {
		if ((snmp_client.chost = malloc(strlen(SNMP_DEFAULT_LOCAL) + 1))
		    == NULL) {
			syslog(LOG_ERR, "malloc() failed: %s", strerror(errno));
			return (-1);
		}
		strcpy(snmp_client.chost, SNMP_DEFAULT_LOCAL);
	}

	return (2);
}