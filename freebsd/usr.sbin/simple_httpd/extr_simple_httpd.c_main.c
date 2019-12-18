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
typedef  int pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  O_WRONLY ; 
 int /*<<< orphan*/  WNOHANG ; 
 int /*<<< orphan*/  W_OK ; 
 scalar_t__ access (char*,int /*<<< orphan*/ ) ; 
 int atoi (char*) ; 
 scalar_t__ chdir (char*) ; 
 int /*<<< orphan*/  chmod (char*,int) ; 
 int /*<<< orphan*/  close (int) ; 
 int con_sock ; 
 scalar_t__ daemonize ; 
 int /*<<< orphan*/  exit (int) ; 
 char* fetch_mode ; 
 int fork () ; 
 char* getenv (char*) ; 
 scalar_t__ geteuid () ; 
 int getopt (int,char**,char*) ; 
 char* homedir ; 
 int http_port ; 
 int /*<<< orphan*/  http_request () ; 
 int /*<<< orphan*/  http_sock ; 
 int /*<<< orphan*/  init_servconnection () ; 
 scalar_t__ listen (int /*<<< orphan*/ ,int) ; 
 char* logfile ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 char* optarg ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  puts (char*) ; 
 int /*<<< orphan*/  setpgrp (int,int) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int verbose ; 
 int /*<<< orphan*/  wait3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_connection () ; 

int
main(int argc, char *argv[])
{
	int ch, ld;
	pid_t httpd_group = 65534;
	pid_t server_pid;

	/* Default for html directory */
	strcpy (homedir,getenv("HOME"));
	if (!geteuid())	strcpy (homedir,"/httphome");
	   else		strcat (homedir,"/httphome");

	/* Defaults for log file */
	if (geteuid()) {
	    strcpy(logfile,getenv("HOME"));
	    strcat(logfile,"/");
	    strcat(logfile,"jhttp.log");
	} else 
	  strcpy(logfile,"/var/log/jhttpd.log");

	/* Parse command line arguments */
	while ((ch = getopt(argc, argv, "d:f:g:l:p:vDh")) != -1)
	  switch (ch) {
	  case 'd':
	    strcpy(homedir,optarg);
	    break;	  
	  case 'f':
	    daemonize = 0;
	    verbose = 1;
	    fetch_mode = optarg;
	    break;
	  case 'g':
	    httpd_group = atoi(optarg);
	    break;
	  case 'l':
	    strcpy(logfile,optarg);
	    break;
	  case 'p':
	    http_port = atoi(optarg);
	    break;
	  case 'v':
	    verbose = 1;
	    break;
	  case 'D':
	    daemonize = 0;
	    break;
	  case '?':
	  case 'h':
	  default:
	    printf("usage: simple_httpd [[-d directory][-g grpid][-l logfile][-p port][-vD]]\n");
	    exit(1);
	    /* NOTREACHED */
	  }

	/* Not running as root and no port supplied, assume 1080 */
	if ((http_port == 80) && geteuid()) {
	  http_port = 1080;
	}

	/* Do we really have rights in the html directory? */
	if (fetch_mode == NULL) {
	  if (chdir(homedir)) {
	    perror("chdir");
	    puts(homedir);
	    exit(1);
	  }
	}

	/* Create log file if it doesn't exit */
	if ((access(logfile,W_OK)) && daemonize) {
	  ld = open (logfile,O_WRONLY);
	  chmod (logfile,00600);
	  close(ld);
	}

	init_servconnection();

	if (verbose) {
	  printf("Server started with options \n"); 
	  printf("port: %d\n",http_port);
	  if (fetch_mode == NULL) printf("html home: %s\n",homedir);
	  if (daemonize) printf("logfile: %s\n",logfile);
	}

	/* httpd is spawned */
	if (daemonize) {
	  if ((server_pid = fork()) != 0) {
	    wait3(0,WNOHANG,0);
	    if (verbose) printf("pid: %d\n",server_pid);
	    exit(0);
	  }
	  wait3(0,WNOHANG,0);
	}

	if (fetch_mode == NULL)
		setpgrp((pid_t)0, httpd_group);

	/* How many connections do you want? 
	 * Keep this lower than the available number of processes
	 */
	if (listen(http_sock,15) < 0) exit(1);

	label:	
	wait_connection();

	if (fork()) {
	  wait3(0,WNOHANG,0);
	  close(con_sock);
	  goto label;
	}

	http_request();

	wait3(0,WNOHANG,0);
	exit(0);
}