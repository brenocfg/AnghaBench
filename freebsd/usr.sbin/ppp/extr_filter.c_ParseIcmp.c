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
struct filterent {int f_srcport; void* f_dstop; void* f_srcop; } ;

/* Variables and functions */
 int /*<<< orphan*/  LogWARN ; 
 void* OP_EQ ; 
 void* OP_NONE ; 
 int /*<<< orphan*/  log_Printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strcmp (char const* const,char*) ; 
 int strtol (char const* const,char**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ParseIcmp(int argc, char const *const *argv, struct filterent *tgt)
{
  int type;
  char *cp;

  switch (argc) {
  case 0:
    /* permit/deny all ICMP types */
    tgt->f_srcop = tgt->f_dstop = OP_NONE;
    break;

  case 3:
    if (!strcmp(*argv, "src") && !strcmp(argv[1], "eq")) {
      type = strtol(argv[2], &cp, 0);
      if (cp == argv[2]) {
	log_Printf(LogWARN, "ParseIcmp: type is expected.\n");
	return 0;
      }
      tgt->f_srcop = OP_EQ;
      tgt->f_srcport = type;
      tgt->f_dstop = OP_NONE;
    }
    break;

  default:
    log_Printf(LogWARN, "ParseIcmp: bad icmp syntax.\n");
    return 0;
  }
  return 1;
}