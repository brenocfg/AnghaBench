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
typedef  int /*<<< orphan*/  line ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ fgets (char*,int,int /*<<< orphan*/ *) ; 
 char* ftp_rooted (char*) ; 
 int /*<<< orphan*/  ftpd_pclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ftpd_popen (char*,char*,int,int) ; 
 int /*<<< orphan*/  lreply (int,char*) ; 
 int /*<<< orphan*/  nreply (char*,char*) ; 
 int /*<<< orphan*/  perror_reply (int,char*) ; 
 int /*<<< orphan*/  reply (int,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char*) ; 
 int strlen (char*) ; 

int
find(char *pattern)
{
    char line[1024];
    FILE *f;

    snprintf(line, sizeof(line),
	     "/bin/locate -d %s -- %s",
	     ftp_rooted("/etc/locatedb"),
	     pattern);
    f = ftpd_popen(line, "r", 1, 1);
    if(f == NULL){
	perror_reply(550, "/bin/locate");
	return 1;
    }
    lreply(200, "Output from find.");
    while(fgets(line, sizeof(line), f)){
	if(line[strlen(line)-1] == '\n')
	    line[strlen(line)-1] = 0;
	nreply("%s", line);
    }
    reply(200, "Done");
    ftpd_pclose(f);
    return 0;
}