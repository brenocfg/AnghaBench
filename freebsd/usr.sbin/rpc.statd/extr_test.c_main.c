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
struct sm_stat_res {int dummy; } ;
struct TYPE_3__ {char* my_name; int my_proc; int /*<<< orphan*/  my_vers; int /*<<< orphan*/  my_prog; } ;
struct TYPE_4__ {char* mon_name; TYPE_1__ my_id; } ;
struct mon {TYPE_2__ mon_id; } ;
typedef  int /*<<< orphan*/  CLIENT ;

/* Variables and functions */
 int /*<<< orphan*/  SM_PROG ; 
 int /*<<< orphan*/  SM_VERS ; 
 int /*<<< orphan*/ * clnt_create (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  printf (char*) ; 
 struct sm_stat_res* sm_mon_1 (struct mon*,int /*<<< orphan*/ *) ; 
 void* sm_simu_crash_1 (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcmp (char*,char*) ; 

int main(int argc, char **argv)
{
  CLIENT *cli;
  char dummy;
  void *out;
  struct mon mon;

  if (argc < 2)
  {
    fprintf(stderr, "usage: test <hostname> | crash\n");
    fprintf(stderr, "always talks to statd at localhost\n");
    exit(1);
  }

  printf("Creating client for localhost\n" );
  cli = clnt_create("localhost", SM_PROG, SM_VERS, "udp");
  if (!cli)
  {
    printf("Failed to create client\n");
    exit(1);
  }

  mon.mon_id.mon_name = argv[1];
  mon.mon_id.my_id.my_name = argv[1];
  mon.mon_id.my_id.my_prog = SM_PROG;
  mon.mon_id.my_id.my_vers = SM_VERS;
  mon.mon_id.my_id.my_proc = 1;	/* have it call sm_stat() !!!	*/

  if (strcmp(argv[1], "crash"))
  {
    /* Hostname given		*/
    struct sm_stat_res *res;

    res = sm_mon_1(&mon, cli);
    if (res)
      printf("Success!\n");
    else
      printf("Fail\n");  
  }
  else
  {
    out = sm_simu_crash_1(&dummy, cli);
    if (out)
      printf("Success!\n");
    else
      printf("Fail\n");  
  }

  return 0;
}