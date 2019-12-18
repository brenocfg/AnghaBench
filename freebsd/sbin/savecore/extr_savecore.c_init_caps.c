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
typedef  int /*<<< orphan*/  cap_rights_t ;
typedef  int /*<<< orphan*/  cap_channel_t ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_IOCTL ; 
 int /*<<< orphan*/  CAP_PREAD ; 
 int /*<<< orphan*/  CAP_WRITE ; 
 int /*<<< orphan*/  FA_OPEN ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  O_RDWR ; 
 int /*<<< orphan*/  cap_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cap_init () ; 
 int /*<<< orphan*/  cap_rights_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * cap_service_open (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * capfa ; 
 int /*<<< orphan*/  caph_cache_catpages () ; 
 int /*<<< orphan*/  caph_cache_tzdata () ; 
 scalar_t__ caph_enter_casper () ; 
 int /*<<< orphan*/ * capsyslog ; 
 scalar_t__ checkfor ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/ * fileargs_init (int,char**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ keep ; 
 int /*<<< orphan*/  logmsg (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
init_caps(int argc, char **argv)
{
	cap_rights_t rights;
	cap_channel_t *capcas;

	capcas = cap_init();
	if (capcas == NULL) {
		logmsg(LOG_ERR, "cap_init(): %m");
		exit(1);
	}
	/*
	 * The fileargs capability does not currently provide a way to limit
	 * ioctls.
	 */
	(void)cap_rights_init(&rights, CAP_PREAD, CAP_WRITE, CAP_IOCTL);
	capfa = fileargs_init(argc, argv, checkfor || keep ? O_RDONLY : O_RDWR,
	    0, &rights, FA_OPEN);
	if (capfa == NULL) {
		logmsg(LOG_ERR, "fileargs_init(): %m");
		exit(1);
	}
	caph_cache_catpages();
	caph_cache_tzdata();
	if (caph_enter_casper() != 0) {
		logmsg(LOG_ERR, "caph_enter_casper(): %m");
		exit(1);
	}
	capsyslog = cap_service_open(capcas, "system.syslog");
	if (capsyslog == NULL) {
		logmsg(LOG_ERR, "cap_service_open(system.syslog): %m");
		exit(1);
	}
	cap_close(capcas);
}