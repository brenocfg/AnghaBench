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

/* Variables and functions */
 int /*<<< orphan*/  EX_USAGE ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
usage(const char *msg)
{
	fprintf(stderr, "%s\n", msg);
	fprintf(stderr, "Usage: auditreduce [options] [file ...]\n");
	fprintf(stderr, "\tOptions are : \n");
	fprintf(stderr, "\t-A : all records\n");
	fprintf(stderr, "\t-a YYYYMMDD[HH[[MM[SS]]] : after date\n");
	fprintf(stderr, "\t-b YYYYMMDD[HH[[MM[SS]]] : before date\n");
	fprintf(stderr, "\t-c <flags> : matching class\n");
	fprintf(stderr, "\t-d YYYYMMDD : on date\n");
	fprintf(stderr, "\t-e <uid|name>  : effective user\n");
	fprintf(stderr, "\t-f <gid|group> : effective group\n");
	fprintf(stderr, "\t-g <gid|group> : real group\n");
	fprintf(stderr, "\t-j <pid> : subject id \n");
	fprintf(stderr, "\t-m <evno|evname> : matching event\n");
	fprintf(stderr, "\t-o objecttype=objectvalue\n");
	fprintf(stderr, "\t\t file=<pathname>\n");
	fprintf(stderr, "\t\t msgqid=<ID>\n");
	fprintf(stderr, "\t\t pid=<ID>\n");
	fprintf(stderr, "\t\t semid=<ID>\n");
	fprintf(stderr, "\t\t shmid=<ID>\n");
	fprintf(stderr, "\t-r <uid|name> : real user\n");
	fprintf(stderr, "\t-u <uid|name> : audit user\n");
	fprintf(stderr, "\t-v : select non-matching records\n");
	exit(EX_USAGE);
}