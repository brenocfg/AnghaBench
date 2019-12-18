#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {char* h_name; } ;
struct TYPE_4__ {int /*<<< orphan*/  sin_addr; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  adate () ; 
 scalar_t__ daemonize ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char*) ; 
 TYPE_2__* gethostbyaddr (char*,int,int /*<<< orphan*/ ) ; 
 TYPE_2__* hst ; 
 long inet_addr (char*) ; 
 int /*<<< orphan*/  inet_ntoa (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  logfile ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  putenv (char*) ; 
 TYPE_1__ source ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
log_line(char *req)
{
	char	log_buff[256];
	char	msg[1024];
	char	env_host[80], env_addr[80];
	long	addr;
	FILE	*log;

	strcpy(log_buff,inet_ntoa(source.sin_addr));
	sprintf(env_addr, "REMOTE_ADDR=%s",log_buff);

	addr=inet_addr(log_buff);

	strcpy(msg,adate());
	strcat(msg,"    ");
	hst=gethostbyaddr((char*) &addr, 4, AF_INET);

	/* If DNS hostname exists */
	if (hst) {
	  strcat(msg,hst->h_name);
	  sprintf(env_host, "REMOTE_HOST=%s",hst->h_name);
	}
	strcat(msg," (");
	strcat(msg,log_buff);
	strcat(msg,")   ");
	strcat(msg,req);

	if (daemonize) {
	  log=fopen(logfile,"a");
	  fprintf(log,"%s\n",msg);
	  fclose(log);
	} else
	  printf("%s\n",msg);

	/* This is for CGI scripts */
	putenv(env_addr);
	putenv(env_host);
}