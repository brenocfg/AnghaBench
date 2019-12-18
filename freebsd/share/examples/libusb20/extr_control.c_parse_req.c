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
typedef  int uint8_t ;
struct TYPE_2__ {int bmRequestType; void* wLength; void* wIndex; void* wValue; int /*<<< orphan*/  bRequest; } ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  get_req (char*) ; 
 TYPE_1__ setup ; 
 int /*<<< orphan*/  stderr ; 
 void* strtoul (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
parse_req(int argc, char **argv)
{
  int idx;
  uint8_t rt = 0;

  for (idx = 0; argc != 0 && idx <= 6; argc--, idx++)
    switch (idx)
      {
      case 0:
	/* dir[ection]: i[n] | o[ut] */
	if (*argv[idx] == 'i')
	  rt |= 0x80;
	else if (*argv[idx] == 'o')
	  /* nop */;
	else
	  {
	    fprintf(stderr, "request direction must be \"in\" or \"out\" (got %s)\n",
		    argv[idx]);
	    return -1;
	  }
	break;

      case 1:
	/* type: s[tandard] | c[lass] | v[endor] */
	if (*argv[idx] == 's')
	  /* nop */;
	else if (*argv[idx] == 'c')
	  rt |= 0x20;
	else if (*argv[idx] == 'v')
	  rt |= 0x40;
	else
	  {
	    fprintf(stderr,
		    "request type must be one of \"standard\", \"class\", or \"vendor\" (got %s)\n",
		    argv[idx]);
	    return -1;
	  }
	break;

      case 2:
	/* rcpt: d[evice], i[nterface], e[ndpoint], o[ther] */
	if (*argv[idx] == 'd')
	  /* nop */;
	else if (*argv[idx] == 'i')
	  rt |= 1;
	else if (*argv[idx] == 'e')
	  rt |= 2;
	else if (*argv[idx] == 'o')
	  rt |= 3;
	else
	  {
	    fprintf(stderr,
		    "recipient must be one of \"device\", \"interface\", \"endpoint\", or \"other\" (got %s)\n",
		    argv[idx]);
	    return -1;
	  }
	setup.bmRequestType = rt;
	break;

      case 3:
	setup.bRequest = get_req(argv[idx]);
	break;

      case 4:
	setup.wValue = strtoul(argv[idx], 0, 0);
	break;

      case 5:
	setup.wIndex = strtoul(argv[idx], 0, 0);
	break;

      case 6:
	setup.wLength = strtoul(argv[idx], 0, 0);
	break;
      }

  return argc;
}