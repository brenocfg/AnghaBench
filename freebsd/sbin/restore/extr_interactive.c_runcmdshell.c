#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct entry {int e_flags; int /*<<< orphan*/  e_ino; } ;
struct TYPE_2__ {void* gl_stat; void* gl_lstat; int /*<<< orphan*/  gl_closedir; int /*<<< orphan*/  gl_readdir; int /*<<< orphan*/  gl_opendir; int /*<<< orphan*/  gl_flags; } ;
struct arglist {scalar_t__ freeglob; TYPE_1__ glob; scalar_t__ argcnt; } ;
typedef  int /*<<< orphan*/  name ;
typedef  int /*<<< orphan*/  ino_t ;
typedef  int /*<<< orphan*/  curdir ;

/* Variables and functions */
 int BUFSIZ ; 
 int /*<<< orphan*/  FORCE ; 
 int /*<<< orphan*/  GLOB_ALTDIRFUNC ; 
 int /*<<< orphan*/  LEAF ; 
 int MAXPATHLEN ; 
 int NEW ; 
 int /*<<< orphan*/  addfile ; 
 int /*<<< orphan*/  canon (char*,char*,int) ; 
 int /*<<< orphan*/  checkrestore () ; 
 int /*<<< orphan*/  createfiles () ; 
 int /*<<< orphan*/  createlinks () ; 
 int /*<<< orphan*/  deletefile ; 
 int /*<<< orphan*/  dflag ; 
 int /*<<< orphan*/  dirlookup (char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  getcmd (char*,char*,char*,int,struct arglist*) ; 
 int /*<<< orphan*/  glob_readdir ; 
 void* glob_stat ; 
 int /*<<< orphan*/  globfree (TYPE_1__*) ; 
 int /*<<< orphan*/  inodetype (int /*<<< orphan*/ ) ; 
 struct entry* lookupname (char*) ; 
 int /*<<< orphan*/  mflag ; 
 int /*<<< orphan*/ * nextarg ; 
 int /*<<< orphan*/  pathcheck (char*) ; 
 int /*<<< orphan*/  printdumpinfo () ; 
 int /*<<< orphan*/  printlist (char*,char*) ; 
 int /*<<< orphan*/  reset ; 
 int /*<<< orphan*/  rst_closedir ; 
 int /*<<< orphan*/  rst_opendir ; 
 int runshell ; 
 int /*<<< orphan*/  setdirmodes (int /*<<< orphan*/ ) ; 
 scalar_t__ setjmp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  strncmp (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  treescan (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vflag ; 
 scalar_t__ volno ; 

void
runcmdshell(void)
{
	struct entry *np;
	ino_t ino;
	struct arglist arglist;
	char curdir[MAXPATHLEN];
	char name[MAXPATHLEN];
	char cmd[BUFSIZ];

	arglist.freeglob = 0;
	arglist.argcnt = 0;
	arglist.glob.gl_flags = GLOB_ALTDIRFUNC;
	arglist.glob.gl_opendir = rst_opendir;
	arglist.glob.gl_readdir = glob_readdir;
	arglist.glob.gl_closedir = rst_closedir;
	arglist.glob.gl_lstat = glob_stat;
	arglist.glob.gl_stat = glob_stat;
	canon("/", curdir, sizeof(curdir));
loop:
	if (setjmp(reset) != 0) {
		if (arglist.freeglob != 0) {
			arglist.freeglob = 0;
			arglist.argcnt = 0;
			globfree(&arglist.glob);
		}
		nextarg = NULL;
		volno = 0;
	}
	runshell = 1;
	getcmd(curdir, cmd, name, sizeof(name), &arglist);
	switch (cmd[0]) {
	/*
	 * Add elements to the extraction list.
	 */
	case 'a':
		if (strncmp(cmd, "add", strlen(cmd)) != 0)
			goto bad;
		ino = dirlookup(name);
		if (ino == 0)
			break;
		if (mflag)
			pathcheck(name);
		treescan(name, ino, addfile);
		break;
	/*
	 * Change working directory.
	 */
	case 'c':
		if (strncmp(cmd, "cd", strlen(cmd)) != 0)
			goto bad;
		ino = dirlookup(name);
		if (ino == 0)
			break;
		if (inodetype(ino) == LEAF) {
			fprintf(stderr, "%s: not a directory\n", name);
			break;
		}
		(void) strcpy(curdir, name);
		break;
	/*
	 * Delete elements from the extraction list.
	 */
	case 'd':
		if (strncmp(cmd, "delete", strlen(cmd)) != 0)
			goto bad;
		np = lookupname(name);
		if (np == NULL || (np->e_flags & NEW) == 0) {
			fprintf(stderr, "%s: not on extraction list\n", name);
			break;
		}
		treescan(name, np->e_ino, deletefile);
		break;
	/*
	 * Extract the requested list.
	 */
	case 'e':
		if (strncmp(cmd, "extract", strlen(cmd)) != 0)
			goto bad;
		createfiles();
		createlinks();
		setdirmodes(0);
		if (dflag)
			checkrestore();
		volno = 0;
		break;
	/*
	 * List available commands.
	 */
	case 'h':
		if (strncmp(cmd, "help", strlen(cmd)) != 0)
			goto bad;
	case '?':
		fprintf(stderr, "%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s",
			"Available commands are:\n",
			"\tls [arg] - list directory\n",
			"\tcd arg - change directory\n",
			"\tpwd - print current directory\n",
			"\tadd [arg] - add `arg' to list of",
			" files to be extracted\n",
			"\tdelete [arg] - delete `arg' from",
			" list of files to be extracted\n",
			"\textract - extract requested files\n",
			"\tsetmodes - set modes of requested directories\n",
			"\tquit - immediately exit program\n",
			"\twhat - list dump header information\n",
			"\tverbose - toggle verbose flag",
			" (useful with ``ls'')\n",
			"\thelp or `?' - print this list\n",
			"If no `arg' is supplied, the current",
			" directory is used\n");
		break;
	/*
	 * List a directory.
	 */
	case 'l':
		if (strncmp(cmd, "ls", strlen(cmd)) != 0)
			goto bad;
		printlist(name, curdir);
		break;
	/*
	 * Print current directory.
	 */
	case 'p':
		if (strncmp(cmd, "pwd", strlen(cmd)) != 0)
			goto bad;
		if (curdir[1] == '\0')
			fprintf(stderr, "/\n");
		else
			fprintf(stderr, "%s\n", &curdir[1]);
		break;
	/*
	 * Quit.
	 */
	case 'q':
		if (strncmp(cmd, "quit", strlen(cmd)) != 0)
			goto bad;
		return;
	case 'x':
		if (strncmp(cmd, "xit", strlen(cmd)) != 0)
			goto bad;
		return;
	/*
	 * Toggle verbose mode.
	 */
	case 'v':
		if (strncmp(cmd, "verbose", strlen(cmd)) != 0)
			goto bad;
		if (vflag) {
			fprintf(stderr, "verbose mode off\n");
			vflag = 0;
			break;
		}
		fprintf(stderr, "verbose mode on\n");
		vflag++;
		break;
	/*
	 * Just restore requested directory modes.
	 */
	case 's':
		if (strncmp(cmd, "setmodes", strlen(cmd)) != 0)
			goto bad;
		setdirmodes(FORCE);
		break;
	/*
	 * Print out dump header information.
	 */
	case 'w':
		if (strncmp(cmd, "what", strlen(cmd)) != 0)
			goto bad;
		printdumpinfo();
		break;
	/*
	 * Turn on debugging.
	 */
	case 'D':
		if (strncmp(cmd, "Debug", strlen(cmd)) != 0)
			goto bad;
		if (dflag) {
			fprintf(stderr, "debugging mode off\n");
			dflag = 0;
			break;
		}
		fprintf(stderr, "debugging mode on\n");
		dflag++;
		break;
	/*
	 * Unknown command.
	 */
	default:
	bad:
		fprintf(stderr, "%s: unknown command; type ? for help\n", cmd);
		break;
	}
	goto loop;
}