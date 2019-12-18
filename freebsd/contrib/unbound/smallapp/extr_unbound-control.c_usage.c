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
 char* CONFIGFILE ; 
 char* PACKAGE_BUGREPORT ; 
 char* PACKAGE_VERSION ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
usage(void)
{
	printf("Usage:	local-unbound-control [options] command\n");
	printf("	Remote control utility for unbound server.\n");
	printf("Options:\n");
	printf("  -c file	config file, default is %s\n", CONFIGFILE);
	printf("  -s ip[@port]	server address, if omitted config is used.\n");
	printf("  -q		quiet (don't print anything if it works ok).\n");
	printf("  -h		show this usage help.\n");
	printf("Commands:\n");
	printf("  start				start server; runs unbound(8)\n");
	printf("  stop				stops the server\n");
	printf("  reload			reloads the server\n");
	printf("  				(this flushes data, stats, requestlist)\n");
	printf("  stats				print statistics\n");
	printf("  stats_noreset			peek at statistics\n");
#ifdef HAVE_SHMGET
	printf("  stats_shm			print statistics using shm\n");
#endif
	printf("  status			display status of server\n");
	printf("  verbosity <number>		change logging detail\n");
	printf("  log_reopen			close and open the logfile\n");
	printf("  local_zone <name> <type>	add new local zone\n");
	printf("  local_zone_remove <name>	remove local zone and its contents\n");
	printf("  local_data <RR data...>	add local data, for example\n");
	printf("				local_data www.example.com A 192.0.2.1\n");
	printf("  local_data_remove <name>	remove local RR data from name\n");
	printf("  local_zones, local_zones_remove, local_datas, local_datas_remove\n");
	printf("  				same, but read list from stdin\n");
	printf("  				(one entry per line).\n");
	printf("  dump_cache			print cache to stdout\n");
	printf("  load_cache			load cache from stdin\n");
	printf("  lookup <name>			print nameservers for name\n");
	printf("  flush <name>			flushes common types for name from cache\n");
	printf("  				types:  A, AAAA, MX, PTR, NS,\n");
	printf("					SOA, CNAME, DNAME, SRV, NAPTR\n");
	printf("  flush_type <name> <type>	flush name, type from cache\n");
	printf("  flush_zone <name>		flush everything at or under name\n");
	printf("  				from rr and dnssec caches\n");
	printf("  flush_bogus			flush all bogus data\n");
	printf("  flush_negative		flush all negative data\n");
	printf("  flush_stats 			flush statistics, make zero\n");
	printf("  flush_requestlist 		drop queries that are worked on\n");
	printf("  dump_requestlist		show what is worked on by first thread\n");
	printf("  flush_infra [all | ip] 	remove ping, edns for one IP or all\n");
	printf("  dump_infra			show ping and edns entries\n");
	printf("  set_option opt: val		set option to value, no reload\n");
	printf("  get_option opt		get option value\n");
	printf("  list_stubs			list stub-zones and root hints in use\n");
	printf("  list_forwards			list forward-zones in use\n");
	printf("  list_insecure			list domain-insecure zones\n");
	printf("  list_local_zones		list local-zones in use\n");
	printf("  list_local_data		list local-data RRs in use\n");
	printf("  insecure_add zone 		add domain-insecure zone\n");
	printf("  insecure_remove zone		remove domain-insecure zone\n");
	printf("  forward_add [+i] zone addr..	add forward-zone with servers\n");
	printf("  forward_remove [+i] zone	remove forward zone\n");
	printf("  stub_add [+ip] zone addr..	add stub-zone with servers\n");
	printf("  stub_remove [+i] zone		remove stub zone\n");
	printf("		+i		also do dnssec insecure point\n");
	printf("		+p		set stub to use priming\n");
	printf("  forward [off | addr ...]	without arg show forward setup\n");
	printf("				or off to turn off root forwarding\n");
	printf("				or give list of ip addresses\n");
	printf("  ratelimit_list [+a]		list ratelimited domains\n");
	printf("  ip_ratelimit_list [+a]	list ratelimited ip addresses\n");
	printf("		+a		list all, also not ratelimited\n");
	printf("  list_auth_zones		list auth zones\n");
	printf("  auth_zone_reload zone		reload auth zone from zonefile\n");
	printf("  auth_zone_transfer zone	transfer auth zone from master\n");
	printf("  view_list_local_zones	view	list local-zones in view\n");
	printf("  view_list_local_data	view	list local-data RRs in view\n");
	printf("  view_local_zone view name type  	add local-zone in view\n");
	printf("  view_local_zone_remove view name  	remove local-zone in view\n");
	printf("  view_local_data view RR...		add local-data in view\n");
	printf("  view_local_datas view 		add list of local-data to view\n");
	printf("  					one entry per line read from stdin\n");
	printf("  view_local_data_remove view name  	remove local-data in view\n");
	printf("Version %s\n", PACKAGE_VERSION);
	printf("BSD licensed, see LICENSE in source package for details.\n");
	printf("Report bugs to %s\n", PACKAGE_BUGREPORT);
	exit(1);
}