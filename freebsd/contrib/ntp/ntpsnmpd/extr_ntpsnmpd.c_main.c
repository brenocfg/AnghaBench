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

/* Variables and functions */
 int /*<<< orphan*/  AGENTXSOCKET ; 
 int /*<<< orphan*/  HAVE_OPT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOG_INFO ; 
 int /*<<< orphan*/  NETSNMP_DS_AGENT_ROLE ; 
 int /*<<< orphan*/  NETSNMP_DS_AGENT_X_SOCKET ; 
 int /*<<< orphan*/  NETSNMP_DS_APPLICATION_ID ; 
 int /*<<< orphan*/  NOFORK ; 
 int /*<<< orphan*/  OPT_ARG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGTERM ; 
 int /*<<< orphan*/  SOCK_CLEANUP ; 
 int /*<<< orphan*/  SOCK_STARTUP ; 
 int /*<<< orphan*/  SYSLOG ; 
 int /*<<< orphan*/  agent_check_and_process (int) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  init_agent (char*) ; 
 int /*<<< orphan*/  init_ntpSnmpSubagentObject () ; 
 int /*<<< orphan*/  init_snmp (char*) ; 
 int keep_running ; 
 scalar_t__ netsnmp_daemonize (int,int) ; 
 int /*<<< orphan*/  netsnmp_ds_set_boolean (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netsnmp_ds_set_string (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntpq_closehost () ; 
 scalar_t__ ntpq_openhost (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntpsnmpdOptions ; 
 int optionProcess (int /*<<< orphan*/ *,int,char**) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snmp_enable_calllog () ; 
 int /*<<< orphan*/  snmp_enable_stderrlog () ; 
 int /*<<< orphan*/  snmp_log (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  snmp_shutdown (char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stop_server ; 

int
main (int argc, char **argv) {
  int background = 0; /* start as background process */
  int use_syslog = 1; /* use syslog for logging */

	{
		int optct = optionProcess(&ntpsnmpdOptions, argc, argv);
		argc -= optct;
		argv += optct;
	}

	if (!HAVE_OPT(NOFORK))
		background = 1;

	if (!HAVE_OPT(SYSLOG))
		use_syslog = 0;

  /* using the net-snmp syslog facility */
  if (use_syslog)
    snmp_enable_calllog();
  else
    snmp_enable_stderrlog();

  /* Become Subagent */
    netsnmp_ds_set_boolean(NETSNMP_DS_APPLICATION_ID, NETSNMP_DS_AGENT_ROLE, 1);
 
  /* go into background mode, if requested */
  if (background && netsnmp_daemonize(1, !use_syslog))
      exit(1);

  /* Now register with the master Agent X process */

  /* call Netsnmp socket startup macro, which will initialize the network stuff if required */
  SOCK_STARTUP;

  /* Set AgentX socket interface */
  netsnmp_ds_set_string(NETSNMP_DS_APPLICATION_ID,
                            NETSNMP_DS_AGENT_X_SOCKET, OPT_ARG( AGENTXSOCKET ));

  init_agent("ntpsnmpd");

  /* Try to connect to ntpd */
  if ( ntpq_openhost("localhost", 0) == 0 )
  {
	fprintf(stderr, "Error: Could not connect to ntpd. Aborting.\n");
	exit(1);
  }
  

  /* Register callback functions ...  */
  init_ntpSnmpSubagentObject();  
  init_snmp("ntpsnmpd");

  /* Signal handler */
  keep_running = 1;
  signal(SIGTERM, stop_server);
  signal(SIGINT, stop_server);

  snmp_log(LOG_INFO,"ntpsnmpd started.\n");
  
  /* main loop here... */
  while(keep_running) {
	agent_check_and_process(1); /* 0 == don't block */
  }

  /* at shutdown time */
  ntpq_closehost();
  snmp_shutdown("ntpsnmpd");
  SOCK_CLEANUP;

  return 0;
}