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
struct gctl_req {char* error; } ;
struct g_command {int gc_flags; int /*<<< orphan*/  (* gc_func ) (struct gctl_req*,unsigned int) ;int /*<<< orphan*/  gc_name; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  EXIT_SUCCESS ; 
 int /*<<< orphan*/  GEOM_CLASS_CMDS ; 
 int /*<<< orphan*/  GEOM_STD_CMDS ; 
 int G_FLAG_LOADKLD ; 
 int /*<<< orphan*/  bzero (char*,int) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 struct g_command* find_command (char*,int /*<<< orphan*/ ) ; 
 char* gclass_name ; 
 int /*<<< orphan*/  gctl_free (struct gctl_req*) ; 
 struct gctl_req* gctl_get_handle () ; 
 char* gctl_issue (struct gctl_req*) ; 
 int /*<<< orphan*/  gctl_ro_param (struct gctl_req*,char*,int,char*) ; 
 int /*<<< orphan*/  gctl_rw_param (struct gctl_req*,char*,int,char*) ; 
 int /*<<< orphan*/  load_module () ; 
 int /*<<< orphan*/  parse_arguments (struct g_command*,struct gctl_req*,int*,char***) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 unsigned int set_flags (struct g_command*) ; 
 int /*<<< orphan*/  std_available (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 scalar_t__ strncmp (char const*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct gctl_req*,unsigned int) ; 
 int /*<<< orphan*/  usage () ; 
 scalar_t__ verbose ; 
 char* version ; 
 int /*<<< orphan*/  warnx (char*,char const*) ; 

__attribute__((used)) static void
run_command(int argc, char *argv[])
{
	struct g_command *cmd;
	struct gctl_req *req;
	const char *errstr;
	char buf[4096];

	/* First try to find a command defined by a class. */
	cmd = find_command(argv[0], GEOM_CLASS_CMDS);
	if (cmd == NULL) {
		/* Now, try to find a standard command. */
		cmd = find_command(argv[0], GEOM_STD_CMDS);
		if (cmd == NULL) {
			warnx("Unknown command: %s.", argv[0]);
			usage();
		}
		if (!std_available(cmd->gc_name)) {
			warnx("Command '%s' not available; "
			    "try 'load' first.", argv[0]);
			exit(EXIT_FAILURE);
		}
	}
	if ((cmd->gc_flags & G_FLAG_LOADKLD) != 0)
		load_module();

	req = gctl_get_handle();
	gctl_ro_param(req, "class", -1, gclass_name);
	gctl_ro_param(req, "verb", -1, argv[0]);
	if (version != NULL)
		gctl_ro_param(req, "version", sizeof(*version), version);
	parse_arguments(cmd, req, &argc, &argv);

	bzero(buf, sizeof(buf));
	if (cmd->gc_func != NULL) {
		unsigned flags;

		flags = set_flags(cmd);
		cmd->gc_func(req, flags);
		errstr = req->error;
	} else {
		gctl_rw_param(req, "output", sizeof(buf), buf);
		errstr = gctl_issue(req);
	}
	if (errstr != NULL && errstr[0] != '\0') {
		warnx("%s", errstr);
		if (strncmp(errstr, "warning: ", strlen("warning: ")) != 0) {
			gctl_free(req);
			exit(EXIT_FAILURE);
		}
	}
	if (buf[0] != '\0')
		printf("%s", buf);
	gctl_free(req);
	if (verbose)
		printf("Done.\n");
	exit(EXIT_SUCCESS);
}