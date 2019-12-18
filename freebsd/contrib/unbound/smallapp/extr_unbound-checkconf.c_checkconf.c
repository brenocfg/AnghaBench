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
struct config_file {int /*<<< orphan*/  module_conf; } ;
typedef  int /*<<< orphan*/  oldwd ;

/* Variables and functions */
 int chdir (char*) ; 
 int /*<<< orphan*/  check_auth (struct config_file*) ; 
 int /*<<< orphan*/  check_fwd (struct config_file*) ; 
 int /*<<< orphan*/  check_hints (struct config_file*) ; 
 int /*<<< orphan*/  check_mod (struct config_file*,int /*<<< orphan*/ ) ; 
 struct config_file* config_create () ; 
 int /*<<< orphan*/  config_delete (struct config_file*) ; 
 int /*<<< orphan*/  config_read (struct config_file*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fatal_exit (char*) ; 
 int /*<<< orphan*/  getcwd (char*,int) ; 
 int /*<<< orphan*/  iter_get_funcblock () ; 
 int /*<<< orphan*/  log_err (char*,char*,...) ; 
 int /*<<< orphan*/  morechecks (struct config_file*) ; 
 int /*<<< orphan*/  print_option (struct config_file*,char const*,int) ; 
 int /*<<< orphan*/  printf (char*,char const*) ; 
 int /*<<< orphan*/  pythonmod_get_funcblock () ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 scalar_t__ strstr (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  val_get_funcblock () ; 

__attribute__((used)) static void
checkconf(const char* cfgfile, const char* opt, int final)
{
	char oldwd[4096];
	struct config_file* cfg = config_create();
	if(!cfg)
		fatal_exit("out of memory");
	oldwd[0] = 0;
	if(!getcwd(oldwd, sizeof(oldwd))) {
		log_err("cannot getcwd: %s", strerror(errno));
		oldwd[0] = 0;
	}
	if(!config_read(cfg, cfgfile, NULL)) {
		/* config_read prints messages to stderr */
		config_delete(cfg);
		exit(1);
	}
	if(oldwd[0] && chdir(oldwd) == -1)
		log_err("cannot chdir(%s): %s", oldwd, strerror(errno));
	if(opt) {
		print_option(cfg, opt, final);
		config_delete(cfg);
		return;
	}
	morechecks(cfg);
	check_mod(cfg, iter_get_funcblock());
	check_mod(cfg, val_get_funcblock());
#ifdef WITH_PYTHONMODULE
	if(strstr(cfg->module_conf, "python"))
		check_mod(cfg, pythonmod_get_funcblock());
#endif
	check_fwd(cfg);
	check_hints(cfg);
	check_auth(cfg);
	printf("unbound-checkconf: no errors in %s\n", cfgfile);
	config_delete(cfg);
}