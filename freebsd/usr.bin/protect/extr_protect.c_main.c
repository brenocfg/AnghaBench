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
typedef  int /*<<< orphan*/  idtype_t ;
typedef  int /*<<< orphan*/  id_t ;

/* Variables and functions */
 scalar_t__ ENOENT ; 
 int PPROT_CLEAR ; 
 int PPROT_DESCEND ; 
 int PPROT_INHERIT ; 
 int PPROT_SET ; 
 int /*<<< orphan*/  PROC_SPROTECT ; 
 int /*<<< orphan*/  P_PGID ; 
 int /*<<< orphan*/  P_PID ; 
 int /*<<< orphan*/  err (int,char*,...) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  execvp (char*,char**) ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  getpid () ; 
 int /*<<< orphan*/  optarg ; 
 scalar_t__ optind ; 
 int /*<<< orphan*/  parse_id (int /*<<< orphan*/ ) ; 
 int procctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  usage () ; 

int
main(int argc, char *argv[])
{
	idtype_t idtype;
	id_t id;
	int ch, flags;
	bool descend, inherit, idset;

	idtype = P_PID;
	id = getpid();
	flags = PPROT_SET;
	descend = inherit = idset = false;
	while ((ch = getopt(argc, argv, "cdig:p:")) != -1)
		switch (ch) {
		case 'c':
			flags = PPROT_CLEAR;
			break;
		case 'd':
			descend = true;
			break;
		case 'i':
			inherit = true;
			break;
		case 'g':
			idtype = P_PGID;
			id = parse_id(optarg);
			idset = true;
			break;
		case 'p':
			idtype = P_PID;
			id = parse_id(optarg);
			idset = true;
			break;
		}
	argc -= optind;
	argv += optind;

	if ((idset && argc != 0) || (!idset && (argc == 0 || descend)))
		usage();

	if (descend)
		flags |= PPROT_DESCEND;
	if (inherit)
		flags |= PPROT_INHERIT;
	if (procctl(idtype, id, PROC_SPROTECT, &flags) == -1)
		err(1, "procctl");

	if (argc != 0) {
		errno = 0;
		execvp(*argv, argv);
		err(errno == ENOENT ? 127 : 126, "%s", *argv);
	}
	return (0);
}