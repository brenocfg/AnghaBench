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
 int /*<<< orphan*/  checkconf (char const*,char const*,int) ; 
 int /*<<< orphan*/  checklock_start () ; 
 int /*<<< orphan*/  checklock_stop () ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  log_ident_set (char*) ; 
 int /*<<< orphan*/  log_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* optarg ; 
 scalar_t__ optind ; 
 int /*<<< orphan*/  usage () ; 
 char* w_lookup_reg_str (char*,char*) ; 

int main(int argc, char* argv[])
{
	int c;
	int final = 0;
	const char* f;
	const char* opt = NULL;
	const char* cfgfile = CONFIGFILE;
	log_ident_set("unbound-checkconf");
	log_init(NULL, 0, NULL);
	checklock_start();
#ifdef USE_WINSOCK
	/* use registry config file in preference to compiletime location */
	if(!(cfgfile=w_lookup_reg_str("Software\\Unbound", "ConfigFile")))
		cfgfile = CONFIGFILE;
#endif /* USE_WINSOCK */
	/* parse the options */
	while( (c=getopt(argc, argv, "fho:")) != -1) {
		switch(c) {
		case 'f':
			final = 1;
			break;
		case 'o':
			opt = optarg;
			break;
		case '?':
		case 'h':
		default:
			usage();
		}
	}
	argc -= optind;
	argv += optind;
	if(argc != 0 && argc != 1)
		usage();
	if(argc == 1)
		f = argv[0];
	else	f = cfgfile;
	checkconf(f, opt, final);
	checklock_stop();
	return 0;
}