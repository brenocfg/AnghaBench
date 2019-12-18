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
struct config_strlist {int /*<<< orphan*/  str; struct config_strlist* next; } ;
struct config_file {struct config_strlist* auto_trust_anchor_file_list; int /*<<< orphan*/  pidfile; } ;

/* Variables and functions */
 int /*<<< orphan*/  config_get_option (struct config_file*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  config_print_func ; 
 int /*<<< orphan*/  fatal_exit (char*,...) ; 
 char* fname_after_chroot (int /*<<< orphan*/ ,struct config_file*,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  stdout ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static void
print_option(struct config_file* cfg, const char* opt, int final)
{
	if(strcmp(opt, "pidfile") == 0 && final) {
		char *p = fname_after_chroot(cfg->pidfile, cfg, 1);
		if(!p) fatal_exit("out of memory");
		printf("%s\n", p);
		free(p);
		return;
	}
	if(strcmp(opt, "auto-trust-anchor-file") == 0 && final) {
		struct config_strlist* s = cfg->auto_trust_anchor_file_list;
		for(; s; s=s->next) {
			char *p = fname_after_chroot(s->str, cfg, 1);
			if(!p) fatal_exit("out of memory");
			printf("%s\n", p);
			free(p);
		}
		return;
	}
	if(!config_get_option(cfg, opt, config_print_func, stdout))
		fatal_exit("cannot print option '%s'", opt);
}