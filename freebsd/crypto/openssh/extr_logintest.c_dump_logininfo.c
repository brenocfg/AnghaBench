#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int sa_family; } ;
struct TYPE_4__ {TYPE_1__ sa; } ;
struct logininfo {char* progname; int type; int pid; int uid; char* line; char* username; char* hostname; int exit; int termination; int tv_sec; int tv_usec; TYPE_2__ hostaddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,char*,char*,int,int,int,char*,char*,char*,int,int,int,int,int) ; 

void
dump_logininfo(struct logininfo *li, char *descname)
{
	/* yes I know how nasty this is */
	printf("struct logininfo %s = {\n\t"
	       "progname\t'%s'\n\ttype\t\t%d\n\t"
	       "pid\t\t%d\n\tuid\t\t%d\n\t"
	       "line\t\t'%s'\n\tusername\t'%s'\n\t"
	       "hostname\t'%s'\n\texit\t\t%d\n\ttermination\t%d\n\t"
	       "tv_sec\t%d\n\ttv_usec\t%d\n\t"
	       "struct login_netinfo hostaddr {\n\t\t"
	       "struct sockaddr sa {\n"
	       "\t\t\tfamily\t%d\n\t\t}\n"
	       "\t}\n"
	       "}\n",
	       descname, li->progname, li->type,
	       li->pid, li->uid, li->line,
	       li->username, li->hostname, li->exit,
	       li->termination, li->tv_sec, li->tv_usec,
	       li->hostaddr.sa.sa_family);
}