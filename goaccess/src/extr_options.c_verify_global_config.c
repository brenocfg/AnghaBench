#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int load_global_config; int /*<<< orphan*/  iconfigfile; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EOF ; 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 TYPE_3__ conf ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int getopt_long (int,char**,int /*<<< orphan*/ ,TYPE_1__*,int*) ; 
 TYPE_1__* long_opts ; 
 int /*<<< orphan*/  optarg ; 
 int optind ; 
 int /*<<< orphan*/  short_options ; 
 int /*<<< orphan*/  strcmp (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xstrdup (int /*<<< orphan*/ ) ; 

void
verify_global_config (int argc, char **argv)
{
  int o, idx = 0;

  conf.load_global_config = 1;
  while ((o = getopt_long (argc, argv, short_options, long_opts, &idx)) >= 0) {
    if (-1 == o || EOF == o)
      break;

    switch (o) {
    case 'p':
      conf.iconfigfile = xstrdup (optarg);
      break;
    case 0:
      if (!strcmp ("no-global-config", long_opts[idx].name))
        conf.load_global_config = 0;
      break;
    case '?':
      exit (EXIT_FAILURE);
    }
  }

  /* reset it to 1 */
  optind = 1;
}